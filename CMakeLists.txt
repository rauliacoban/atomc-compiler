cmake_minimum_required(VERSION 3.23.0)

project(my_compiler LANGUAGES CXX)

#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++2a")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall")

set(ENV{BOOST_ROOT} "/usr/local/boost_1_79_0")
set(BOOST_ROOT "/usr/local/boost_1_79_0") 

set(UHD_BOOST_REQUIRED_COMPONENTS
    program_options
    system
    thread
)
set(BOOST_MIN_VERSION 1.78)

### Make the executable #######################################################
set(SOURCES
    main.cpp
    log.hpp
    log.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
