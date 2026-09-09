#include "mini/vector.hpp"
#include <cassert>
#include <memory>

struct Counter {
    static inline long default_ctor = 0;
    static inline long value_ctor   = 0;
    static inline long copy_ctor    = 0;
    static inline long move_ctor    = 0;
    static inline long dtor         = 0;

    int payload[16]{};  // add something more than counting so the compiler can't do any funny business when optimizing

    Counter() { ++default_ctor; }
    explicit Counter(int v) { payload[0] = v; ++value_ctor; }
    Counter(const Counter& o) : payload{} {
        std::copy(std::begin(o.payload), std::end(o.payload), payload);
        ++copy_ctor;
    }
    Counter(Counter&& o) noexcept : payload{} {
        std::copy(std::begin(o.payload), std::end(o.payload), payload);
        ++move_ctor;
    }
    ~Counter() { ++dtor; }

    static void reset() {
        default_ctor = copy_ctor = move_ctor = dtor = value_ctor = 0;
    }
};

// asserting that no copies or moves are made
static void verify_emplace_back_no_temporary() {
    Counter::reset();
    {
        mini::vector<Counter> v;
        v.reserve(1);
        v.emplace_back(42);   // should hit value_ctor directly, nothing else
    }
    assert(Counter::value_ctor == 1);
    assert(Counter::copy_ctor  == 0);
    assert(Counter::move_ctor  == 0);

    Counter::reset();
    {
        mini::vector<Counter> v;
        v.reserve(1);
        Counter t(42);
        v.push_back(std::move(t));   // should be 1 move, 0 copies
    }
    assert(Counter::value_ctor == 1);
    assert(Counter::copy_ctor  == 0);
    assert(Counter::move_ctor  == 1);
}

int main() {
    verify_emplace_back_no_temporary();

    return 0;
}
