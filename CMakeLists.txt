cmake_minimum_required(VERSION 3.26)
project(program LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

add_executable(program main.cpp)

configure_file(inputData ${CMAKE_BINARY_DIR}/)
configure_file(inputDataExtended ${CMAKE_BINARY_DIR}/)