cmake_minimum_required(VERSION 3.24)

cmake_minimum_required(VERSION 3.24)
project(SECOND LANGUAGES CXX)

add_compile_options(-std=c++23)
file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
include_directories(include/)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})