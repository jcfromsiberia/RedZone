cmake_minimum_required (VERSION 2.6)

project(RedZoneTest)

# turn on C++11 features
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

set(RZT_SOURCES
    main.cpp
)

set(RZT_HEADERS
)

add_subdirectory(libRedZone)

include_directories(${RedZone_SOURCE_DIR}/src)

add_executable(RedZoneTest ${RZT_SOURCES} ${RZT_HEADERS})

target_link_libraries(RedZoneTest RedZone)
