#include <vector>
#include <benchmark/benchmark.h>
#include "wrappers.h"
#include "benchmark_administrator.h"

/**
 * https://github.com/google/benchmark suggests running this in release:
 * -DCMAKE_BUILD_TYPE=Release
 *
 * Also, disable CPU scaling:
 * sudo cpupower frequency-set --governor performance
 * ./rcc8.reasoner.lib.benchmarks
 * sudo cpupower frequency-set --governor powersave
 */

// this is not pretty, but should work...
auto g_administrator = BenchmarkAdministrator ();

template<class T_reasoner>
void Test (benchmark::State& state)
    {
    size_t n = state.range (0);

    auto relations = g_administrator.GetOrGenerateRelations (n, 1, 1, 1, 1, 10, 10, 1);
    auto reasoner = T_reasoner (n, relations);

    bool satisfiable;
    for (auto _ : state)
        satisfiable = reasoner.IsSatisfiable ();

    g_administrator.RegisterResult (state, satisfiable);
    }

#define BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS(n)      \
        BENCHMARK_TEMPLATE (Test, QsrWrapper)->Arg (n); \
        BENCHMARK_TEMPLATE (Test, GqrWrapper)->Arg (n);

BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (10);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (50);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (100);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (250);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (500);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (750);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (1000);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (1500);
BENCHMARK_IMPLEMENTATIONS_FOR_NUMB_VARS (2000);

BENCHMARK_MAIN ();
