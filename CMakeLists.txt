cmake_minimum_required(VERSION 3.26)
project(program LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)


include(cmake/UseClangTidy.cmake)

add_subdirectory(task1)
add_subdirectory(task2)

