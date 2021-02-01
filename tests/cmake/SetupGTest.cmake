#From example https://github.com/google/googletest/blob/master/googletest/README.md

configure_file (cmake/CMakeLists.gtest.txt.in googletest-download/CMakeLists.txt)
execute_process (
    COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)

if (result)
    message (FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()

execute_process (
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)

if (result)
    message (FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory (
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL
)

add_subdirectory (rcc8.reasoner.lib.tests)