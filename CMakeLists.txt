cmake_minimum_required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -O3 -march=native")
include_directories(parcxx/src)
add_subdirectory(src)
