project (recfile_open_test)
cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)


set (MAIN recfile_open_test)
add_executable (${MAIN} ${MAIN}.cpp)


find_package (MetavisionSDK COMPONENTS core driver REQUIRED)
target_link_libraries (
    ${MAIN}
    MetavisionSDK::core
    MetavisionSDK::driver
    )
