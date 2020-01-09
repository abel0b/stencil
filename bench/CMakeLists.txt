add_custom_target(
    bench
    COMMAND source_dir=${CMAKE_SOURCE_DIR} bash "${CMAKE_SOURCE_DIR}/bench/bench.sh"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/src"
    DEPENDS stencil-baseline stencil-openmp
)
