cmake_minimum_required(VERSION 3.16)
project(F_Rocks)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

add_executable(F_Rocks main.cpp)