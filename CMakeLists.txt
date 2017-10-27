cmake_minimum_required(VERSION 3.6)
project(Grader)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp classroom.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(Grader ${SOURCE_FILES} classroom.h)