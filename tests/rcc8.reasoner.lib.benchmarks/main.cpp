#include <vector>
#include <benchmark/benchmark.h>
#include <QSR/rcc8.h>

/**
 * https://github.com/google/benchmark suggests running this in release:
 * -DCMAKE_BUILD_TYPE=Release
 *
 * Also, disable CPU scaling:
 * sudo cpupower frequency-set --governor performance
 * ./rcc8.reasoner.lib.benchmarks
 * sudo cpupower frequency-set --governor powersave
 */

void Test(benchmark::State& state)
    {
    auto relations = std::vector<qsr::rcc8::Relation> ();
    size_t n = state.range (0) / 2;

    for (size_t i = 0; i < n / 2; i++)
        {
        relations.push_back ({i, n - i, qsr::rcc8::RelationType::PO});
        relations.push_back ({i, i + 1, qsr::rcc8::RelationType::TPP});
        }

    auto network = qsr::rcc8::ConstraintNetwork (state.range (0), relations);

    bool satisfiable = true;
    for (auto _ : state)
        satisfiable = satisfiable && network.IsSatisfiable ();

    if (!satisfiable)
        state.SkipWithError ("Incorrect result computed.");
    }

BENCHMARK (Test)->Arg(1000);

BENCHMARK_MAIN();
