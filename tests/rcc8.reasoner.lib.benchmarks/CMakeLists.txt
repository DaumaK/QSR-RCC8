add_executable (
    rcc8.reasoner.lib.benchmarks
    main.cpp
)

target_link_libraries (
    rcc8.reasoner.lib.benchmarks
    rcc8.reasoner.lib
    benchmark::benchmark
)