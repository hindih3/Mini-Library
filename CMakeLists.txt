cmake_minimum_required(VERSION 3.16)
project(mini_vector CXX)

add_library(mini INTERFACE)
target_include_directories(mini INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(mini INTERFACE cxx_std_20)

option(MINI_SANITIZE "Build tests with ASan+UBSan" OFF)

enable_testing()
add_executable(vector_tests tests/vector_tests.cpp)
target_link_libraries(vector_tests PRIVATE mini)
target_compile_options(vector_tests PRIVATE -Wall -Wextra -Wpedantic)

if(MINI_SANITIZE)
    target_compile_options(vector_tests PRIVATE -fsanitize=address,undefined -g)
    target_link_options(vector_tests PRIVATE -fsanitize=address,undefined)
endif()

add_test(NAME vector_tests COMMAND vector_tests)