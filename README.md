# mini::vector

A from-scratch reimplementation of `std::vector` in C++20: a single-header,
templated dynamic array built over an explicit allocate / construct / destroy
layer, the way `std::allocator` separates raw storage from object lifetime.

## Design
- Raw storage and lifetime are separated: `allocate`/`deallocate` wrap global
  `operator new`/`delete`; `construct`/`destroy` manage object lifetime.
- A `std::is_trivially_copyable` fast path uses `memcpy`/`memmove`; other types
  go through element-wise construction.
- The growth and copy-assignment paths are strongly exception-safe: a throwing
  element constructor rolls back the partially built buffer and rethrows,
  leaving the original vector untouched.
- Full random-access `iterator` / `const_iterator`, usable with `<algorithm>`.

## Use
Header-only; add the include root:

    g++ -std=c++20 -Iinclude your_program.cpp

```cpp
#include "mini/vector.hpp"
mini::vector<int> v{1, 2, 3};
v.push_back(4);
```

## Limitations
- Not `std::allocator`-aware; uses global `operator new`/`delete`, no support
  for over-aligned types.
- No `emplace_back` or move-only element support yet.
- `insert`/`erase` take an index rather than an iterator.