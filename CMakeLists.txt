cmake_minimum_required(VERSION 3.0)
project(karatsuba)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Int.h)
add_executable(karatsuba ${SOURCE_FILES})