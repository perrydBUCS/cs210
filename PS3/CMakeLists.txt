# cmake_minimum_required(VERSION <specify CMake version here>)
project(PS3 C)

set(CMAKE_C_STANDARD 99)

add_executable(PS3 main.c node.c node.h list.c list.h)