cmake_minimum_required(VERSION 3.28)

project(INTERVIEWS LANGUAGES CXX)

# file(GLOB SOURCES src/*.cpp) <- this didn't work

set(SOURCES
    src/queue.cpp
    src/move.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)