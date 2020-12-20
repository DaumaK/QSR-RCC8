add_library (
    rcc8.reasoner.lib
    include/QSR/rcc8.h
    internal/reasoner_internal.h
    src/region.cpp
    src/modal_world.cpp
    src/reasoner_utils.cpp
    src/solution_context.cpp
    src/constraint_network.cpp
    )

target_include_directories (rcc8.reasoner.lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (rcc8.reasoner.lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/internal)