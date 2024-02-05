cmake_minimum_required(VERSION 3.24)

project(UDFS LANGUAGES CXX)

# add_compile_options(-std=c++23)

# add_library(${PROJECT_NAME} GLOB src/udfs_main.cpp)
file(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)