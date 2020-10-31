add_library (
    rcc8.reasoner.lib
    QSR/rcc8.h
    )

# temporary fix for cmake not knowing what language this is.
set_target_properties(rcc8.reasoner.lib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories (rcc8.reasoner.lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})