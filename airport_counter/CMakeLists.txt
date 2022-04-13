cmake_minimum_required(VERSION 3.16)
project(coursera)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_DEBUG "-O2")

include_directories(C:/Users/aochi/CLionProjects/coursera)
add_executable(
        coursera
        ../test_runner.h
        ../profile.h
        airport_counter.cpp
)