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
    size_t dcProb = state.range (1);
    size_t ecProb = state.range (2);
    size_t poProb = state.range (3);
    size_t eqProb = state.range (4);
    size_t tppProb = state.range (5);
    size_t ntppProb = state.range (6);
    size_t noneProb = state.range (7);

    auto relations = g_administrator.GenerateRelations (n, dcProb, ecProb, poProb, eqProb, tppProb, ntppProb, noneProb);
    auto reasoner = T_reasoner (n, relations);

    for (auto _ : state)
        reasoner.IsSatisfiable ();
    }

#define BENCH_REGION_COUNTS { 10, 50, 100, 250, 500, 750, 1000, 1500, 2000 }
#define BENCH_PROBABILITIES std::vector<std::vector<int64_t> > { \
    /*(dc, ec, po, eq, tpp, ntpp, none)*/                        \
    { 1, 1, 1, 1, 1, 1, 6 },                                     \
    { 1, 1, 1, 0, 1, 1, 5 },                                     \
    { 1, 1, 1, 0, 3, 3, 9 },                                     \
    { 0, 0, 0, 0, 1, 1, 2 }                                      \
    }

void GenerateArguments (benchmark::internal::Benchmark* bench)
    {
    bench->ArgNames ({ "region count", "dc", "ec", "po", "eq", "tpp", "ntpp", "none" });
    for (int64_t regionCount : BENCH_REGION_COUNTS)
        {
        for (std::vector<int64_t> probabilities : BENCH_PROBABILITIES)
            {
            std::vector<int64_t> args = { regionCount };
            args.insert (args.end (), probabilities.begin (), probabilities.end ());
            bench->Args (args);
            }
        }
    }

BENCHMARK_TEMPLATE (Test, QsrWrapper)->Apply (GenerateArguments);
//BENCHMARK_TEMPLATE (Test, GqrWrapper)->Apply (GenerateArguments)->Repetitions (5);

BENCHMARK_MAIN ();
