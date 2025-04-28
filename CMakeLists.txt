cmake_minimum_required(VERSION 4.0.1)
project(Bount-Graphics-Project LANGUAGES CXX)

option(BUILD_BOUNT_GRAPHICS_EXAMPLES "BUILD BOUNT GRAPHICS EXAMPLES" OFF)
option(BUILD_BOUNT_EXAMPLES "BUILD ALL BOUNT EXAMPLES" OFF)

include("${CMAKE_CURRENT_LIST_DIR}/.cmake/config.cmake")

load_env_cmake()

update_bount_git_module(Core main)
update_bount_git_module(glm master)

load_github_binaries(GLEW 2.2.0)
load_github_binaries(SDL 3.2.8)

if(NOT TARGET Bount-Graphics-Library)
    project(Bount-Graphics-Library)

    add_subdirectory(${BOUNT_CORE_MODULE} Core)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/.module/glm")

    create_bount_library_vars(BOUNT_GRAPHICS)
    add_library(Bount-Graphics SHARED)
    target_sources(Bount-Graphics
    PRIVATE
        ${BOUNT_GRAPHICS_CXX_SRC}
        ${BOUNT_GRAPHICS_CXX_MODULE_SRC}
    PUBLIC
        FILE_SET bount_graphics_cxx_headers TYPE HEADERS
        BASE_DIRS ${BOUNT_GRAPHICS_CXX_INCLUDE_DIR}
        FILES ${BOUNT_GRAPHICS_CXX_HEADER_FILES}
    PUBLIC
        FILE_SET bount_graphics_cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${BOUNT_GRAPHICS_CXX_MODULE_DIR}
        FILES ${BOUNT_GRAPHICS_CXX_MODULE_FILES}
    )
    target_precompile_headers(Bount-Graphics
        PRIVATE
            "${BOUNT_GRAPHICS_CXX_INCLUDE_DIR}/Bount/Event/Precompiled.hpp"
            "${BOUNT_GRAPHICS_CXX_INCLUDE_DIR}/Bount/Graphics/Precompiled.hpp"
            "${BOUNT_GRAPHICS_CXX_INCLUDE_DIR}/Bount/Window/Precompiled.hpp"
    )

    target_link_libraries(Bount-Graphics PUBLIC Bount::Core OpenGL::GL glm::glm glew::all sdl::all)
    set_bount_library_api_macros(Bount-Graphics BOUNT_EVENT BOUNT_GRAPHICS BOUNT_WINDOW)
    set_bount_library_common_properties(Bount-Graphics)
    add_library(Bount::Graphics ALIAS Bount-Graphics)

    copy_bount_resources(Bount-Graphics-Resources Bount-Graphics)
endif()

if((BUILD_BOUNT_GRAPHICS_EXAMPLES OR BUILD_BOUNT_EXAMPLES) AND (NOT TARGET Bount-Graphics-Examples))
    project(Bount-Graphics-Examples)

    list(APPEND BOUNT_GRAPHICS_EXAMPLES Window)
    foreach(example ${BOUNT_GRAPHICS_EXAMPLES})
        file(GLOB_RECURSE BOUNT_GRAPHICS_EXAMPLE_${example}_SRC
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cc"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cxx"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.c++"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cpp"
        )
        add_executable(Bount-Graphics-Example-${example} ${BOUNT_GRAPHICS_EXAMPLE_${example}_SRC})
        target_include_directories(Bount-Graphics-Example-${example} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/include")
        target_link_libraries(Bount-Graphics-Example-${example} PRIVATE Bount::Graphics)
        set_bount_example_common_properties(Bount-Graphics-Example-${example} ${example})
    endforeach()
endif()
