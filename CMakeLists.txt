# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.1.5)
project(test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        BinaryTree.h
        BinaryTree.cpp
        )



add_library(tree BinaryTree.cpp)

add_executable(test ${SOURCE_FILES})