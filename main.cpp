#include <iostream>
#include <vector>
#include <chrono>
#include "vector"

constexpr size_t N = 30'000'000;

int main() {
    using clock = std::chrono::high_resolution_clock;

    // std::vector test
    {
        std::vector<int> v;
        auto start = clock::now();

        for (size_t i = 0; i < N; ++i)
            v.push_back(i);

        auto end = clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "std::vector push_back: "
                  << elapsed.count() << " seconds\n";
    }

    // mini::vector test
    {
        mini::vector<int> v;
        auto start = clock::now();

        for (size_t i = 0; i < N; ++i)
            v.push_back(i);

        auto end = clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "mini::vector push_back: "
                  << elapsed.count() << " seconds\n";
    }
}
