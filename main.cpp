#include <iostream>
#include <vector>
#include <chrono>
#include "vector"
#include <cstring>

constexpr size_t N = 50'000'000;

int main()
{
    mini::vector<int> v(10);
    for (size_t i = 0; i < v.size(); i++)
    {
        v[i] = i;
    }

    for (auto& i : v)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    v.erase(0);

    for (auto& i : v)
    {
        std::cout << i << ' ';
    }
    
    
    
}

/*
using clock = std::chrono::high_resolution_clock;

    // std::vector test
    {
        std::vector<std::string> v;
        auto start = clock::now();

        for (size_t i = 0; i < N; ++i)
            v.push_back("--------------------------------------------------");

        auto end = clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "std::vector push_back: "
                  << elapsed.count() << " seconds\n";
    }

    // mini::vector test
    {
        mini::vector<std::string> v;
        auto start = clock::now();

        for (size_t i = 0; i < N; ++i)
            v.push_back("--------------------------------------------------");

        auto end = clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout << "mini::vector push_back: "
                  << elapsed.count() << " seconds\n";
    }
                  */
