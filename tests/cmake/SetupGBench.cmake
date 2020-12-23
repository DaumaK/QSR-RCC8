#From example https://github.com/google/googletest/blob/master/googletest/README.md

configure_file (cmake/CMakeLists.gbench.txt.in googlebenchmark-download/CMakeLists.txt)
execute_process (
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download
)

if (result)
    message (FATAL_ERROR "CMake step for googlebenchmark failed: ${result}")
endif ()

execute_process (
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download
)

if (result)
    message (FATAL_ERROR "CMake step for googlebenchmark failed: ${result}")
endif ()

add_subdirectory (
    ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-src
    ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-build
    EXCLUDE_FROM_ALL
)

include (cmake/SetupGqr.cmake)

add_subdirectory (rcc8.reasoner.lib.benchmarks)