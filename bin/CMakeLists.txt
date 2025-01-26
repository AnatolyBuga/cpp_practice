cmake_minimum_required(VERSION 3.24)
# Set project name
project(FIRST LANGUAGES CXX VERSION 2.0)
set(CMAKE_CXX_STANDARD 23)
# add_compile_options(-std=c++23 -fmodules-ts)
file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
include_directories(include/ )

# List of files to exclude
set(EXCLUDED_FILE "src/optional/my_sqrt.cpp")

# Remove the excluded file from the list
list(REMOVE_ITEM PROJECT_SOURCE_FILES ${EXCLUDED_FILE})

# add the binary tree to the search path for include files
# so that we will find cmakeConfig.hpp
configure_file(cmakeConfig.h.in cmakeConfig.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
# ORDER MATTERS!
target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_link_libraries(${PROJECT_NAME}
    PUBLIC # optional
    sub::lib1
    sub::lib2
    udfs_compiler_flags # compiler flags defined in udfs cmake
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

# https://cmake.org/cmake/help/latest/guide/tutorial/Adding%20a%20Library.html
# cd build
# cmake .. -DUSE_MY_SQRT=OFF
# cmake --build .
# bin/first.exe
#  cmake --build . --target clean
OPTION(USE_MY_SQRT "Use my own sqrt implementation" ON)
if(USE_MY_SQRT)
  message("Using My SQRT")
  # If USE_MYMATH then USE_MYMATH_SQRT flag can be used in .cpp source files in #ifdef statement
  target_compile_definitions(${PROJECT_NAME} PRIVATE "USE_MY_SQRT")

  # creeat a library, just for the optional file
  add_library(SqrtLib STATIC
    src/optional/my_sqrt.cpp
  )

  # link the library
  target_link_libraries(${PROJECT_NAME} PRIVATE SqrtLib)
else()
  message("Not Using My SQRT")
endif()

# This essentially creates .exe file
# similar to add_executable, but remember for this we need cmake --intall .
set(installable_libs ${PROJECT_NAME})
if(TARGET SqrtLib) # check is such target exists
  list(APPEND installable_libs SqrtLib)
endif()
install(TARGETS ${installable_libs} DESTINATION ${CMAKE_BINARY_DIR}/install/lib)
# install include headers - this only copies header files
install(FILES include/lib.hpp DESTINATION ${CMAKE_BINARY_DIR}/install/include)

# Example cuda
# # Add a custom command to compile the CUDA source file
# Just an example - in reality this is redundant, since COMPILE_LANGUAGE is CUDA for 
# set_source_files_properties(kernel.cu PROPERTIES LANGUAGE CUDA) # this is property
# get_source_file_property(_cuda_lang_and_id kernel.cu COMPILE_LANG_AND_ID) 
# check if compile lang is indeed cuda
# must be explicitly set

# # Check if CUDA is used and set compiler options accordingly
# if(_cuda_lang_and_id)
#     separate_arguments(_cuda_lang_and_id)
#     list(GET _cuda_lang_and_id 0 _cuda_lang)
#     list(GET _cuda_lang_and_id 1 _cuda_id)
#     if(_cuda_lang STREQUAL "CUDA")
#         target_compile_options(my_executable PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--gpu-architecture=compute_75>)
#     endif()
# endif()

target_compile_options(${PROJECT_NAME} INTERFACE
# wrap in build interface to see during builds only
# note gcc_like_cxx is defined in top level 
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

include(CTest)

# does the application run
add_test(NAME Runs COMMAND ${PROJECT_NAME} 25)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS Runs)