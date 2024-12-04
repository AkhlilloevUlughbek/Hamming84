cmake_minimum_required(VERSION 3.10)

project(hamming)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(hamming hamming.h hamming.cpp)

add_executable(prog main.cpp)

target_link_libraries(prog PRIVATE hamming)