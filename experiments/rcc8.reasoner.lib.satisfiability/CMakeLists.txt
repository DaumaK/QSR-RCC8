add_executable (
    rcc8.reasoner.lib.satisfiability
    main.cpp
)

target_link_libraries (rcc8.reasoner.lib.satisfiability PRIVATE rcc8.reasoner.lib)