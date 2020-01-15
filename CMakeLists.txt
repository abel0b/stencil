cmake_minimum_required(VERSION 3.0)

project(stencil LANGUAGES C)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CUDA_COMPILER "nvcc")

find_package(OpenMP REQUIRED)
find_package(CUDA)

set(STENCIL_VERSIONS "baseline" "seq" "simd" "openmp")

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)

