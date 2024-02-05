cmake_minimum_required(VERSION 3.24)

project(UDFS LANGUAGES CXX)

# file(GLOB SOURCES src/*.cpp) <- this didn't work

set(SOURCES
    src/vector.cpp
    src/udfs_main.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)