cmake_minimum_required(VERSION 3.27)
project(Assignment3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assignment3 main.cpp
        HashTable.cpp
        MyMalloc.cpp
        HashTable.h
        MyMalloc.h)
