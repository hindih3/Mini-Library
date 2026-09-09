#include <benchmark/benchmark.h>
#include "mini/vector.hpp"
#include <vector>
#include <string>
#include <malloc.h>

// Test speed difference between emplace_back and push_back
// Both cases get reserved upfront since growth allocation only interferes with results

// push_back
template <class Vec>
static void BM_push_back(benchmark::State& state) {
    const int n = state.range(0);          // N comes from the range, not a constant
    for (auto _ : state) {                  // the framework decides how many reps
        Vec v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) {
            std::string s(30, 'a'); // avoiding SSO
            v.push_back(std::move(s));
        }
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * n);
}

// emplace_back
template <class Vec>
static void BM_emplace_back(benchmark::State& state) {
    const int n = state.range(0);
    for (auto _ : state) {
        Vec v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) {
            v.emplace_back(30, 'a');
        }
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * n);
}

// Register each template instantiation across a range of N.
BENCHMARK(BM_push_back<mini::vector<std::string>>)->RangeMultiplier(2)->Range(1<<10, 1<<18);
BENCHMARK(BM_push_back<std::vector<std::string>>)->RangeMultiplier(2)->Range(1<<10, 1<<18);
BENCHMARK(BM_emplace_back<mini::vector<std::string>>)->RangeMultiplier(2)->Range(1<<10, 1<<18);
BENCHMARK(BM_emplace_back<std::vector<std::string>>)->RangeMultiplier(2)->Range(1<<10, 1<<18);

int main(int argc, char** argv) {
    mallopt(M_MMAP_THRESHOLD, 1 << 26);
    mallopt(M_MMAP_MAX, 0);
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}