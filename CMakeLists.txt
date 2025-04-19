cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Development" "Release" "RelWithDebInfo" "MinSizeRel")
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} UPPER_config)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_config} "${CMAKE_BINARY_DIR}/${config}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_config} "${CMAKE_BINARY_DIR}/${config}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_config} "${CMAKE_BINARY_DIR}/${config}/lib")
endforeach()

set(BOUNT_CORE_MODULE "${CMAKE_CURRENT_LIST_DIR}/Core")
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/Custom.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/Custom.cmake")
endif()

if(NOT TARGET Bount::GL)
    project(Bount-GL)

    # Modules
    add_subdirectory(${BOUNT_CORE_MODULE} Core)

    # Extensions
    set(SDL_VERSION 3.2.8)
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}.zip")
        file(DOWNLOAD "https://github.com/Softloq/SDL-Prebuilt/releases/download/v${SDL_VERSION}/sdl-win64-msvc.zip" "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}.zip" SHOW_PROGRESS)
    endif()
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}")
        file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}.zip" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}/config.cmake")
    find_package(SDL3 REQUIRED CONFIG PATHS "external/sdl-${SDL_VERSION}/cmake")

    set(GLEW_VERSION 2.2.0)
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}.zip")
        file(DOWNLOAD "https://github.com/Softloq/GLEW-Prebuilt/releases/download/v${GLEW_VERSION}/glew-win64-msvc.zip" "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}.zip" SHOW_PROGRESS)
    endif()
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}")
        file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}.zip" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}/config.cmake")
    find_package(OpenGL REQUIRED)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/glm")

    # Includes
    set(Bount_GL_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

    # Sources
    file(GLOB_RECURSE Bount_GL_SRC
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cc")

    # Building
    add_library(Bount-GL SHARED ${Bount_GL_SRC})
    set_target_properties(Bount-GL PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
    target_compile_definitions(Bount-GL PRIVATE BOUNT_GL_BUILD_API)
    target_compile_definitions(Bount-GL PUBLIC BOUNT_GL_USE_API)
    target_include_directories(Bount-GL PUBLIC ${Bount_GL_INCLUDE_DIRS})
    target_link_libraries(Bount-GL PUBLIC Bount::Core sdl::all OpenGL::GL glew::all glm::glm)
    target_precompile_headers(Bount-GL PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/Bount/GL/Precompiled.hpp")
    add_library(Bount::GL ALIAS Bount-GL)
endif()
