#include <iostream>
#include <vector>
#include <chrono>
#include "vector"
#include <cstring>

constexpr size_t N = 50'000'000;

int main()
{
    int x[5] = {1, 2, 3, 4, 5};
    int y[5];
    memmove(y, x, sizeof(int) * 5);
    x[2] = 0;
    for (int i = 0; i < 5; i++)
    {
        std::cout << x[i] << ' ' << y[i] << '\n';
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
