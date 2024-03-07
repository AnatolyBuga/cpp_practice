cmake_minimum_required(VERSION 3.24)
# Set project name
project(FIRST LANGUAGES CXX VERSION 2.0)
set(CMAKE_CXX_STANDARD 23)
# add_compile_options(-std=c++23 -fmodules-ts)
file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
include_directories(include/ )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
configure_file(cmakeConfig.h.in cmakeConfig.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
# ORDER MATTERS!
target_include_directories(FIRST PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_link_libraries(${PROJECT_NAME}
    sub::lib1
    sub::lib2
    # OpenMP::OpenMP_CXX
)
OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
  FIND_PACKAGE(OpenMP)
  IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  ENDIF()
ENDIF()