cmake_minimum_required(VERSION 3.26)
project(MainSolution)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainSolution main.cpp
        exceptions.h
        additionalFunctions.h
        fileService.h
        main.cpp)
