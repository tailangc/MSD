cmake_minimum_required(VERSION 3.27)
project(Cryptography)

set(CMAKE_CXX_STANDARD 17)

add_executable(Cryptography main.cpp
        blockCipher.cpp
        RC4.cpp)
