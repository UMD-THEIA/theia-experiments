project (eventsstream_test)
cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)


set (MAIN eventsstream_test)
add_executable (${MAIN} ${MAIN}.cpp)

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package (MetavisionHAL REQUIRED)
target_link_libraries (
    ${MAIN}
    Metavision::HAL_discovery
    ${Boost_LIBRARIES}
    )
