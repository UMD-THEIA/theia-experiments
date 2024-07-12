project (TimesurfaceLib)
cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 17)


set (MAIN TimesurfaceLib)
add_library (${MAIN} ${MAIN}.cpp)


find_package (MetavisionSDK COMPONENTS core driver REQUIRED)
target_link_libraries (${MAIN} MetavisionSDK::core MetavisionSDK::driver)