cmake_minimum_required (VERSION 3.0)
project (rcc8.reasoner CXX)

enable_testing ()

add_subdirectory (rcc8.reasoner.lib)
add_subdirectory (rcc8.reasoner.cli)
add_subdirectory (tests)