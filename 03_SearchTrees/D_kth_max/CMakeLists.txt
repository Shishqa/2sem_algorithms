cmake_minimum_required(VERSION 3.15)
project(D_kth_max)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_CXX_STANDARD 17)

add_executable(D_kth_max main.cpp)