cmake_minimum_required(VERSION 3.16)
project(mini_vector CXX)

add_library(mini INTERFACE)
target_include_directories(mini INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mini INTERFACE cxx_std_20)

option(MINI_SANITIZE   "Build tests with ASan+UBSan" OFF)
option(MINI_BENCHMARKS "Build benchmarks"            OFF)

# Default to Release if the user didn't pick one (matters for benchmark subbuild)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

enable_testing()

add_executable(vector_tests tests/vector_tests.cpp)
target_link_libraries(vector_tests PRIVATE mini)
target_compile_options(vector_tests PRIVATE -Wall -Wextra -Wpedantic)

if(MINI_SANITIZE)
    target_compile_options(vector_tests PRIVATE -fsanitize=address,undefined -g)
    target_link_options(vector_tests    PRIVATE -fsanitize=address,undefined)
endif()

add_test(NAME vector_tests COMMAND vector_tests)

if(MINI_BENCHMARKS)
    include(FetchContent)
    set(BENCHMARK_ENABLE_TESTING      OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL      OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_GTEST_TESTS  OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
            benchmark
            GIT_REPOSITORY https://github.com/google/benchmark.git
            GIT_TAG        v1.9.1
    )
    FetchContent_MakeAvailable(benchmark)

    add_executable(vector_bench benchmarks/vector_bench.cpp)
    target_link_libraries(vector_bench PRIVATE mini benchmark::benchmark)
    target_compile_options(vector_bench PRIVATE -O2 -DNDEBUG)
endif()