cmake_minimum_required(VERSION 3.5)
project(HashMap)

set(CMAKE_CXX_STANDARD 14)

add_executable(HashMap main.cpp hash_map.cpp hash_map.h test.cpp test.h framework.h)