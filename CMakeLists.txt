cmake_minimum_required (VERSION 2.8)
project(OptBinTree)

SET(CMAKE_CXX_STANDARD 11)

if(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})
  message(FATAL_ERROR "Building in the source tree is not allowed")
endif(PROJECT_BINARY_DIR STREQUAL ${PROJECT_SOURCE_DIR})

# the search paths
include_directories(${PROJECT_SOURCE_DIR}/include/)

add_executable(opt_bin_tree ${PROJECT_SOURCE_DIR}/src/main.cxx ${PROJECT_SOURCE_DIR}/src/Build_OptBinTree.cxx)
add_executable(my_fancy_executable ${PROJECT_SOURCE_DIR}/src/build_histogram.cxx)
