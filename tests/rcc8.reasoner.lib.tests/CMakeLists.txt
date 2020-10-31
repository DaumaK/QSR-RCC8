add_executable (
    rcc8.reasoner.lib.tests
    main.cpp
    relation_tests.cpp
    )

target_link_libraries (
    rcc8.reasoner.lib.tests
    rcc8.reasoner.lib
    gtest_main
    )

add_test (
    NAME rcc8.reasoner.lib.tests
    COMMAND rcc8.reasoner.lib.tests
    )