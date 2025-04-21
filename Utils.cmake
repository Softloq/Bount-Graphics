# Define Configurations
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug" "Development" "Release" "RelWithDebInfo" "MinSizeRel")
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} UPPER_CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/${config}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/${config}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_CONFIG} "${CMAKE_BINARY_DIR}/${config}/lib")
endforeach()

function(bount_create_module_update_target OUTPUT_NAME MODULE_LIST)
    add_custom_target(${OUTPUT_NAME} DEPENDS "${CMAKE_CURRENT_LIST_DIR}/__run_always")
    foreach(module ${${MODULE_LIST}})
        add_custom_target(${OUTPUT_NAME}-${module}-Module-Update
            DEPENDS "${CMAKE_CURRENT_LIST_DIR}/__run_always"
            COMMENT "Updating ${module} Git Module"
            WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${module}"
            COMMAND git submodule update --init --recursive
            COMMAND git submodule update --recursive
            COMMAND git pull origin)
        add_dependencies(${OUTPUT_NAME} ${OUTPUT_NAME}-${module}-Module-Update)
    endforeach()
endfunction()