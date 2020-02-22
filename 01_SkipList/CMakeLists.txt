cmake_minimum_required(VERSION 3.15)
project(skiplist)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -g -O4")

add_executable(skiplist main.cpp)