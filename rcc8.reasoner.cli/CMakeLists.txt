add_executable (
    rcc8.reasoner.cli
    test_ex.cpp
    )

target_link_libraries (rcc8.reasoner.cli PRIVATE rcc8.reasoner.api)