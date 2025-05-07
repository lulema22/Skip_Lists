cmake_minimum_required(VERSION 3.30)
project(skip_list)

set(CMAKE_CXX_STANDARD 20)

add_executable(skip_list main.cpp
        skip_lists.h
        DynamicArrayNew.h
)
