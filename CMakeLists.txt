cmake_minimum_required(VERSION 3.21)
project(CG2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CG2022
        engine.cpp
        engine.h
        generator.cpp
        generator.h)
