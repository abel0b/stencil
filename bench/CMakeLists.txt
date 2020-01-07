add_custom_target(
    bench
    COMMAND bash "${CMAKE_SOURCE_DIR}/bench/bench.sh"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/src"
    DEPENDS stencil-baseline stencil-openmp
)
