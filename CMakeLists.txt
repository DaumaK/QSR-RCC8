cmake_minimum_required (VERSION 3.0)
project (rcc8.reasoner CXX)

set (CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_CXX_STANDARD 20)

enable_testing ()

add_subdirectory (rcc8.reasoner.lib)
add_subdirectory (rcc8.reasoner.cli)
add_subdirectory (tests)