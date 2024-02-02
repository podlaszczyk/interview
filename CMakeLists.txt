cmake_minimum_required(VERSION 3.26)
project(program LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

find_package(Catch2 REQUIRED)

add_executable(add-test
        add-test.cpp)


target_link_libraries(add-test PRIVATE Catch2::Catch2WithMain)


configure_file(inputData ${CMAKE_BINARY_DIR}/)
configure_file(inputDataExtended ${CMAKE_BINARY_DIR}/)

