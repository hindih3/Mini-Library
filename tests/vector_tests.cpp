#include "mini/vector.hpp"
#include <cassert>
#include <memory>

int main() {
    mini::vector<std::unique_ptr<int>> v;
    auto ptr = std::make_unique<int>();

    v.push_back(std::move(ptr));

    return 0;
}
