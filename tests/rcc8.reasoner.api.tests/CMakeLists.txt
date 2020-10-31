add_executable (
    rcc8.reasoner.api.tests
    main.cpp
    test_test.cpp
    )

target_link_libraries (
    rcc8.reasoner.api.tests
    rcc8.reasoner.api
    gtest_main
    )

add_test (
    NAME rcc8.reasoner.api.tests
    COMMAND rcc8.reasoner.api.tests
    )