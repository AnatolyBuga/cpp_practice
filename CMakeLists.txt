cmake_minimum_required(VERSION 3.24)
project(BOOK LANGUAGES CXX VERSION 1.0) # prject name
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-std=c++23 -fopenmp)
add_subdirectory(bin)
add_subdirectory(udfs)
add_subdirectory(interviews)
add_subdirectory(mypymodule)