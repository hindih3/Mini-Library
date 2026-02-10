#include <iostream>
#include <vector>
#include <chrono>
#include "vector"
#include <cstring>

constexpr size_t N = 5'000'000;
using high_res_clock = std::chrono::high_resolution_clock;

int main()
{
    mini::vector<std::string> s;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
    {
        s.push_back("A");
    }
    auto end   = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "mini::vector push_back: " << elapsed.count() << " seconds\n";
    
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N / 2; i++)
    {
        s.erase(s.size() - 500);
    }
    end   = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "mini::vector erase: " << elapsed.count() << " seconds\n";


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
