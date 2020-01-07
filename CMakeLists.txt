cmake_minimum_required(VERSION 3.0)

project(stencil)

enable_testing()

find_package(OpenMP)
if(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)

