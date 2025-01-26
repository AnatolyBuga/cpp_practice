cmake_minimum_required(VERSION 3.24)
project(BOOK LANGUAGES CXX VERSION 1.0) # prject name

# It seems those get overriden below for OpenMP
set(CMAKE_C_COMPILER "C:\\msys64\\mingw64\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "C:\\msys64\\mingw64\\bin\\g++.exe")

set(CMAKE_AR "gcc-ar")
set(CMAKE_LINKER "gcc-ld")

if (MSVC)
    message("USING MSVC COMPILER")
    add_compile_options(/Zc:__cplusplus)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # does not produce the json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set gcc_like_cxx to true if compiler is any fo those
# <> means generator expression
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>") 
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
add_compile_options(-std=c++23 -fopenmp)
# enable testing
enable_testing() # order matters

add_subdirectory(bin)
add_subdirectory(udfs)
add_subdirectory(interviews)
add_subdirectory(mypymodule)