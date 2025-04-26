cmake_minimum_required(VERSION 4.0.1)
project(Bount-GL-Project LANGUAGES CXX)

option(BUILD_BOUNT_GL_EXAMPLES "BUILD BOUNT GL EXAMPLES" OFF)
option(BUILD_BOUNT_EXAMPLES "BUILD ALL BOUNT EXAMPLES" OFF)

include("${CMAKE_CURRENT_LIST_DIR}/.cmake/config.cmake")

load_env_cmake()

update_bount_git_module(Core main)
update_bount_git_module(glm master)

load_github_binaries(GLEW 2.2.0)
load_github_binaries(SDL 3.2.8)
find_package(OpenGL REQUIRED)

if(NOT TARGET Bount-GL-Library)
    project(Bount-GL-Library)

    add_subdirectory(${BOUNT_CORE_MODULE} Core)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/.module/glm")

    create_bount_library_vars(BOUNT_GL)
    add_library(Bount-GL SHARED)
    target_sources(Bount-GL
    PRIVATE
        ${BOUNT_GL_CXX_SRC}
        ${BOUNT_GL_CXX_MODULE_SRC}
    PUBLIC
        FILE_SET bount_gl_cxx_headers TYPE HEADERS
        BASE_DIRS ${BOUNT_GL_CXX_INCLUDE_DIR}
        FILES ${BOUNT_GL_CXX_HEADER_FILES}
    PUBLIC
        FILE_SET bount_gl_cxx_modules TYPE CXX_MODULES
        BASE_DIRS ${BOUNT_GL_CXX_MODULE_DIR}
        FILES ${BOUNT_GL_CXX_MODULE_FILES}
    )
    target_precompile_headers(Bount-GL
        PRIVATE
            "${BOUNT_GL_CXX_INCLUDE_DIR}/Bount/Event/Precompiled.hpp"
            "${BOUNT_GL_CXX_INCLUDE_DIR}/Bount/Graphics/Precompiled.hpp"
            "${BOUNT_GL_CXX_INCLUDE_DIR}/Bount/Window/Precompiled.hpp"
    )

    target_link_libraries(Bount-GL PUBLIC Bount::Core OpenGL::GL glm::glm glew::all sdl::all)
    set_bount_library_api_macros(Bount-GL BOUNT_EVENT BOUNT_GRAPHICS BOUNT_WINDOW)
    set_bount_library_common_properties(Bount-GL)
    add_library(Bount::GL ALIAS Bount-GL)

    copy_bount_resources(Bount-GL-Resources Bount-GL)
endif()

if((BUILD_BOUNT_GL_EXAMPLES OR BUILD_BOUNT_EXAMPLES) AND (NOT TARGET Bount-GL-Examples))
    project(Bount-GL-Examples)

    list(APPEND BOUNT_GL_EXAMPLES Window)
    foreach(example ${BOUNT_GL_EXAMPLES})
        file(GLOB_RECURSE BOUNT_GL_EXAMPLE_${example}_SRC
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cc"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cxx"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.c++"
            "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/src/**.cpp"
        )
        add_executable(Bount-GL-Example-${example} ${BOUNT_GL_EXAMPLE_${example}_SRC})
        target_include_directories(Bount-GL-Example-${example} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/examples/${example}/include")
        target_link_libraries(Bount-GL-Example-${example} PRIVATE Bount::GL)
        set_bount_example_common_properties(Bount-GL-Example-${example} ${example})
    endforeach()
endif()
