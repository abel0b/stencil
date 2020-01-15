add_custom_target(
    test
    COMMAND ${CMAKE_COMMAND} -E env versions="${STENCIL_VERSIONS}" bash "${CMAKE_SOURCE_DIR}/test/test.sh"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/src"
    DEPENDS stencil-baseline stencil-seq stencil-simd stencil-openmp stencil-openmp-block
)
