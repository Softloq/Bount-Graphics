cmake_minimum_required(VERSION 3.10)
include("${CMAKE_CURRENT_LIST_DIR}/Utils.cmake")

option(BUILD_BOUNT_GL_EXAMPLES "BUILD BOUNT GL EXAMPLES" OFF)

# Load Environment Variables
set(BOUNT_CORE_MODULE "${CMAKE_CURRENT_LIST_DIR}/Core")
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/.env.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/.env.cmake")
endif()

# Prepares the Module Update Target
list(APPEND BOUNT_GL_MODULES Core)
bount_create_module_update_target(Bount-GL-Update-Modules BOUNT_GL_MODULES)


if(NOT TARGET Bount-GL-Library)
    project(Bount-GL-Library)

    # Load Required Libraries
    add_subdirectory(${BOUNT_CORE_MODULE} Core)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/glm")

    set(SDL_VERSION 3.2.8) # Hardcoded to work with our binaries of them.
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}.zip")
        file(DOWNLOAD "https://github.com/Softloq/SDL-Binaries/releases/download/v${SDL_VERSION}/sdl-win64-msvc.zip" "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}.zip" SHOW_PROGRESS)
    endif()
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}")
        file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}.zip" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/external/sdl-${SDL_VERSION}/config.cmake")
    find_package(SDL3 REQUIRED CONFIG PATHS "external/sdl-${SDL_VERSION}/cmake")

    set(GLEW_VERSION 2.2.0) # Hardcoded to work with our binaries of them.
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}.zip")
        file(DOWNLOAD "https://github.com/Softloq/GLEW-Binaries/releases/download/v${GLEW_VERSION}/glew-win64-msvc.zip" "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}.zip" SHOW_PROGRESS)
    endif()
    if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}")
        file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}.zip" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}")
    endif()
    include("${CMAKE_CURRENT_LIST_DIR}/external/glew-${GLEW_VERSION}/config.cmake")
    find_package(OpenGL REQUIRED)
    
    set(BOUNT_GL_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/include")
    file(GLOB_RECURSE BOUNT_GL_SRC
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/src/**.cc")

    # Building
    add_library(Bount-GL SHARED ${BOUNT_GL_SRC})
    add_dependencies(Bount-GL Bount-GL-Update-Modules)
    set_target_properties(Bount-GL PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
    target_compile_definitions(Bount-GL PRIVATE BOUNT_GL_BUILD_API)
    target_compile_definitions(Bount-GL PUBLIC BOUNT_GL_USE_API)
    target_include_directories(Bount-GL PUBLIC ${BOUNT_GL_INCLUDES})
    target_link_libraries(Bount-GL PUBLIC Bount::Core OpenGL::GL glm::glm glew::all sdl::all)
    target_precompile_headers(Bount-GL PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/Bount/GL/Precompiled.hpp")
    add_library(Bount::GL ALIAS Bount-GL)
endif()

if(BUILD_BOUNT_GL_EXAMPLES AND (NOT TARGET Bount-GL-Examples))
    project(Bount-GL-Examples)

    list(APPEND BOUNT_GL_EXAMPLES Window)
    foreach(example ${BOUNT_GL_EXAMPLES})
        file(GLOB_RECURSE Bount-GL-Example-${example}-SRC
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cpp"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cxx"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cc")
        add_executable(Bount-GL-Example-${example} ${Bount-GL-Example-${example}-SRC})
        set_target_properties(Bount-GL-Example-${example} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/examples"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/$<CONFIG>/examples"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/$<CONFIG>/examples"
            OUTPUT_NAME "${example}")
        target_include_directories(Bount-GL-Example-${example} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/include")
        target_link_libraries(Bount-GL-Example-${example} PRIVATE Bount::GL)
    endforeach()
    
    list(GET BOUNT_GL_EXAMPLES 0 SOME_BOUNT_GL_EXAMPLE)
    add_custom_command(TARGET Bount-GL-Example-${SOME_BOUNT_GL_EXAMPLE}
        POST_BUILD
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/__run_always"
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_BINARY_DIR}/$<CONFIG>/bin" "${CMAKE_BINARY_DIR}/$<CONFIG>/examples")
endif()
