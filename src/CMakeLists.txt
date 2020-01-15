add_executable(
    stencil-baseline
    stencil-baseline.c
)

add_executable(
    stencil-seq
    stencil-seq.c
)

add_executable(
    stencil-simd
    stencil-simd.c
)

set_target_properties(stencil-simd PROPERTIES COMPILE_FLAGS "-mavx -O3")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(
    stencil-openmp
    stencil-openmp.c
)

set_target_properties(stencil-openmp PROPERTIES COMPILE_FLAGS "-mavx -O3")
set_target_properties(stencil-openmp PROPERTIES LINK_FLAGS "-fopenmp")

add_executable(
    stencil-openmp-block
    stencil-openmp-block.c
)

set_target_properties(stencil-openmp-block PROPERTIES COMPILE_FLAGS "-mavx -O3")
set_target_properties(stencil-openmp-block PROPERTIES LINK_FLAGS "-fopenmp")

# set(CMAKE_C_COMPILER "nvcc")

# add_executable(
#     stencil-cuda
#     stencil-cuda.cu
# )
# set_target_properties(stencil-cuda PROPERTIES COMPILE_FLAGS "-mavx -O3")

