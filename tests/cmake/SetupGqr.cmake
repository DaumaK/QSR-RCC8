#From example https://github.com/google/googletest/blob/master/googletest/README.md

if (NOT UNIX)
    message (FATAL_ERROR "benchmarking on non-unix systems is not supported.")
endif ()

configure_file (cmake/CMakeLists.gqr.txt.in gqr-download/CMakeLists.txt)
execute_process (
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gqr-download
)

if (result)
    message (FATAL_ERROR "CMake step for gqr failed: ${result}")
endif ()

execute_process (
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gqr-download
)

if (result)
    message (FATAL_ERROR "CMake step for gqr failed: ${result}")
endif ()

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/gqr-src/_build_/default/gqr/libgqr.so")
    execute_process (
        COMMAND python2 ./waf configure --enable-libgqr
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gqr-src
    )

    execute_process (
        COMMAND python2 ./waf
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gqr-src
    )
endif ()

set (LIBGQR_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/gqr-src/_build_/default/gqr/libgqr.so)
set (LIBGQR_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/gqr-src/gqr)
