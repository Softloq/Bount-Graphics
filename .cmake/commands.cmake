set(COMMANDS_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Load environment variables
macro(load_env_cmake)
    if(EXISTS "${COMMANDS_CURRENT_LIST_DIR}/../.env.cmake")
        include("${COMMANDS_CURRENT_LIST_DIR}/../.env.cmake")
    endif()
endmacro()

# Load the github binaries of our own port of a library.
macro(load_github_binaries LibName LIB_VERSION)
    if(NOT EXISTS "${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}.zip")
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            file(DOWNLOAD "https://github.com/Softloq/${LibName}-Binaries/releases/download/v${LIB_VERSION}/${LibName}-linux-clang.zip" "${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}.zip" SHOW_PROGRESS)
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            file(DOWNLOAD "https://github.com/Softloq/${LibName}-Binaries/releases/download/v${LIB_VERSION}/${LibName}-win64-msvc.zip" "${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}.zip" SHOW_PROGRESS)
        endif()
    endif()
    if(NOT EXISTS "${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}")
        file(ARCHIVE_EXTRACT INPUT "${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}.zip" DESTINATION "${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}")
    endif()
    string(TOLOWER ${LibName} lib_name)
    include("${COMMANDS_CURRENT_LIST_DIR}/../.cache/${LibName}-${LIB_VERSION}/config.cmake")
endmacro()

macro(update_bount_git_module module branch)
    execute_process(
        WORKING_DIRECTORY "${COMMANDS_CURRENT_LIST_DIR}/../.module/${module}"
        COMMAND git submodule update --init --recursive
        COMMAND git submodule update --recursive
        COMMAND git checkout ${branch}
        COMMAND git pull origin
    )
endmacro()

# Create common Bount library variables for a library name.
macro(create_bount_library_vars LIB_NAME)
    set(${LIB_NAME}_CXX_INCLUDE_DIR "${COMMANDS_CURRENT_LIST_DIR}/../include")
    set(${LIB_NAME}_CXX_SRC_DIR "${COMMANDS_CURRENT_LIST_DIR}/../src")
    set(${LIB_NAME}_CXX_MODULE_DIR "${COMMANDS_CURRENT_LIST_DIR}/../module")
    set(${LIB_NAME}_CXX_MODULE_SRC_DIR "${COMMANDS_CURRENT_LIST_DIR}/../impl")
    
    file(GLOB_RECURSE ${LIB_NAME}_CXX_HEADER_FILES
        "${${LIB_NAME}_CXX_INCLUDE_DIR}/**.hh"
        "${${LIB_NAME}_CXX_INCLUDE_DIR}/**.hpp"
        "${${LIB_NAME}_CXX_INCLUDE_DIR}/**.hxx"
    )

    file(GLOB_RECURSE ${LIB_NAME}_CXX_SRC
        "${${LIB_NAME}_CXX_SRC_DIR}/**.cc"
        "${${LIB_NAME}_CXX_SRC_DIR}/**.cxx"
        "${${LIB_NAME}_CXX_SRC_DIR}/**.c++"
        "${${LIB_NAME}_CXX_SRC_DIR}/**.cpp"
    )

    file(GLOB_RECURSE ${LIB_NAME}_CXX_MODULE_FILES
        "${${LIB_NAME}_CXX_MODULE_DIR}/**.ixx"
        "${${LIB_NAME}_CXX_MODULE_DIR}/**.ccm"
        "${${LIB_NAME}_CXX_MODULE_DIR}/**.cxxm"
        "${${LIB_NAME}_CXX_MODULE_DIR}/**.c++m"
        "${${LIB_NAME}_CXX_MODULE_DIR}/**.cppm"
    )

    file(GLOB_RECURSE ${LIB_NAME}_CXX_MODULE_SRC
        "${${LIB_NAME}_CXX_MODULE_SRC_DIR}/**.cc"
        "${${LIB_NAME}_CXX_MODULE_SRC_DIR}/**.cxx"
        "${${LIB_NAME}_CXX_MODULE_SRC_DIR}/**.c++"
        "${${LIB_NAME}_CXX_MODULE_SRC_DIR}/**.cpp"
    )
endmacro()

macro(set_bount_library_common_properties TargetName)
    set(CMAKE_CONFIGURATION_TYPES "Debug" "Development" "Release" "RelWithDebInfo" "MinSizeRel")
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${config} UPPER_CONFIG)
        set_target_properties(${TargetName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/$<CONFIG>/Bin"
            LIBRARY_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/$<CONFIG>/Bin"
            ARCHIVE_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/$<CONFIG>/Lib"
        )
    endforeach()
endmacro()

macro(set_bount_example_common_properties TargetName ExeName)
    set(CMAKE_CONFIGURATION_TYPES "Debug" "Development" "Release" "RelWithDebInfo" "MinSizeRel")
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${config} UPPER_CONFIG)
        set_target_properties(${TargetName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/$<CONFIG>/Bin"
            OUTPUT_NAME "${ExeName}-Example"
        )
    endforeach()
endmacro()

macro(copy_bount_resources TargetName AttachTargetName)
    add_custom_target(${TargetName} COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${COMMANDS_CURRENT_LIST_DIR}/../resources" "${CMAKE_BINARY_DIR}/$<CONFIG>/Resources")
    add_dependencies(${AttachTargetName} ${TargetName})
endmacro()

function(set_bount_library_api_macros TargetName)
    unset(BUILD_API_MACROS)
    unset(USE_API_MACROS)
    
    foreach(arg IN LISTS ARGN)
        list(APPEND BUILD_API_MACROS ${arg}_BUILD_API)
        list(APPEND USE_API_MACROS ${arg}_USE_API)
    endforeach()
    target_compile_definitions(${TargetName}
        PRIVATE ${BUILD_API_MACROS}
        PUBLIC  ${USE_API_MACROS}
    )
endfunction()