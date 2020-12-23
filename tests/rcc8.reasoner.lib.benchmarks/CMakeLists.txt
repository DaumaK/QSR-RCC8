add_executable (
    rcc8.reasoner.lib.benchmarks
    wrappers.h
    benchmark_administrator.h
    utils.h
    main.cpp
)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GOBJECT REQUIRED gobject-2.0)

target_link_libraries (
    rcc8.reasoner.lib.benchmarks
    rcc8.reasoner.lib
    benchmark::benchmark
    ${LIBGQR_LIBRARIES}
    ${GOBJECT_LIBRARIES}
)

target_include_directories (rcc8.reasoner.lib.benchmarks PUBLIC ${GOBJECT_INCLUDE_DIRS} ${LIBGQR_DIRECTORIES})
target_compile_options (rcc8.reasoner.lib.benchmarks PUBLIC ${GOBJECT_CFLAGS_OTHER})