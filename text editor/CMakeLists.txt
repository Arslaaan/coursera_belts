cmake_minimum_required(VERSION 3.16)
project(coursera)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/Users/aochi/CLionProjects/coursera)
add_executable(
        coursera
        ../test_runner.h
        ../profile.h
        text_editor.cpp
)