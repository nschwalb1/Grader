cmake_minimum_required(VERSION 3.6)
project(Grader)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp classroom.h)
add_executable(Grader ${SOURCE_FILES} classroom.h)