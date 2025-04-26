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

include("${CMAKE_CURRENT_LIST_DIR}/commands.cmake")