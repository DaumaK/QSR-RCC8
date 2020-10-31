cmake_minimum_required (VERSION 3.0)
project (rcc8.reasoner)

enable_testing ()

add_subdirectory (rcc8.reasoner.api)
add_subdirectory (rcc8.reasoner.cli)
add_subdirectory (tests)