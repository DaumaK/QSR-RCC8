add_library (
    rcc8.reasoner.api 
    test_lib.h test_lib.cpp
    )

target_include_directories (rcc8.reasoner.api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})