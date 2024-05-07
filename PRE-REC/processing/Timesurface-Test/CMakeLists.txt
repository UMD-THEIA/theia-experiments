project (timesurface_test)
cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)


set (MAIN timesurface_test)
add_executable (${MAIN} ${MAIN}.cpp)


set (TSLIB_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/TimesurfaceLib.hpp")
set (TSLIB_EXEC "${CMAKE_CURRENT_SOURCE_DIR}/src/TimesurfaceLib.cpp")
add_library (tsLib ${TSLIB_EXEC} ${TSLIB_HEADER})
set_target_properties (tsLib PROPERTIES LINKER_LANGUAGE CXX)


add_subdirectory (src)


find_package (MetavisionSDK COMPONENTS core driver REQUIRED)
target_link_libraries (
    ${MAIN}
    tsLib
    MetavisionSDK::core
    MetavisionSDK::driver
)
