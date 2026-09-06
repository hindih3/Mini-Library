#include <benchmark/benchmark.h>
#include "mini/vector.hpp"
#include <vector>
#include <string>
#include <malloc.h>

// --- push_back, no reserve --------------------------------------------------
template <class Vec>
static void BM_push_back(benchmark::State& state) {
    const int n = state.range(0);          // N comes from the range, not a constant
    for (auto _ : state) {                  // the framework decides how many reps
        Vec v;

        for (int i = 0; i < n; ++i) v.push_back(i);
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * n);
}

// --- push_back, reserved ----------------------------------------------------
template <class Vec>
static void BM_push_back_reserved(benchmark::State& state) {
    const int n = state.range(0);
    for (auto _ : state) {
        Vec v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) v.push_back(i);
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * n);
}

// Register each template instantiation across a range of N.
BENCHMARK(BM_push_back<mini::vector<int>>)->RangeMultiplier(2)->Range(1<<10, 1<<25);
BENCHMARK(BM_push_back<std::vector<int>>)->RangeMultiplier(2)->Range(1<<10, 1<<25);
BENCHMARK(BM_push_back_reserved<mini::vector<int>>)->RangeMultiplier(2)->Range(1<<10, 1<<25);
BENCHMARK(BM_push_back_reserved<std::vector<int>>)->RangeMultiplier(2)->Range(1<<10, 1<<25);

int main(int argc, char** argv) {
    mallopt(M_MMAP_THRESHOLD, 1 << 26);
    mallopt(M_MMAP_MAX, 0);
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}