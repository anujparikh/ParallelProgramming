cmake_minimum_required(VERSION 3.6)
project(ParallelProgramming)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Homework4/main.c)
add_executable(ParallelProgramming ${SOURCE_FILES})