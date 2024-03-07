cmake_minimum_required(VERSION 3.24)

project(UDFS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-std=c++23)

# file(GLOB SOURCES src/*.cpp) <- this didn't work

set(SOURCES
    src/vector.cpp
    src/vector_errors.cpp
    src/udfs_main.cpp
    src/enum.cpp
    src/unions.cpp
    src/complex.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)