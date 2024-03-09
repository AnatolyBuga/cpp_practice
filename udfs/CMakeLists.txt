cmake_minimum_required(VERSION 3.24)

project(UDFS LANGUAGES CXX VERSION 3.1)

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

# Creating library
add_library(udfs_compiler_flags INTERFACE)
target_compile_features(udfs_compiler_flags INTERFACE cxx_std_23)
# Compiler warnings, note this propagates to the executable
target_compile_options(udfs_compiler_flags INTERFACE
#   "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
#   "$<${msvc_cxx}:-W3>"
# wrap in build interface to see during builds only
# note gcc_like_cxx is defined in top level 
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
configure_file(cmakeConfigUDF.h.in cmakeConfigUDF.hpp)

# We want to state that anybody linking to MathFunctions needs to include the current 
# source directory, while MathFunctions itself doesn't. This can be
# expressed with an INTERFACE usage requirement. Remember INTERFACE means 
# things that consumers require but the producer doesn't.
#
# the cmakeConfigUDF.hpp file generated in lib1 will be included automatically when
# you link lib1 to lib2. There's no need to specify include directories
# manually in lib2/CMakeLists.txt. This is considered a more modern and
# modular approach compared to directly specifying include directories
# with include_directories.
target_include_directories(${PROJECT_NAME}
                           INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
                           )