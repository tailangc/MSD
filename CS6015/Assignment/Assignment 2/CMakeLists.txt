cmake_minimum_required(VERSION 3.27)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assignment_2 main.cpp
        Expr.cpp
		Expr.h
		cmdline.cpp
		cmdline.h)
