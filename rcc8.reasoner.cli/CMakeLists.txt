add_executable (
    rcc8.reasoner.cli
    main.cpp
    )

target_link_libraries (rcc8.reasoner.cli PRIVATE rcc8.reasoner.lib)