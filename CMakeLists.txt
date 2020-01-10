cmake_minimum_required(VERSION 3.0)

project(stencil)

enable_testing()

find_package(OpenMP)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)

