#pragma once
#include <cstring>
#include <type_traits>
#include <utility>
namespace mini {
    
template <class T>
T* allocate(size_t n) {
    return (n == 0) ? nullptr : static_cast<T*>(::operator new(sizeof(T) * n));
}

template <class T>
void deallocate(T* ptr) noexcept {
    ::operator delete(ptr);
}

template <class T>
void construct(T* ptr) {
    new(ptr) T();
}

template <class T>
void construct(T* ptr, T value) {
    new(ptr) T(value);
}

template <class T>
void copy(T* to, const T* from, size_t n) {
    if constexpr (std::is_trivially_copy_constructible_v<T>)
        std::memcpy(to, from, sizeof(T) * n);
    else
        for (size_t i = 0; i < n; ++i)
            construct(to + i, from[i]);
}

template <typename T>
void destroy(T* ptr) noexcept {
    if constexpr (!std::is_trivially_destructible_v<T>)
        ptr->~T();
}

template <typename T>
void destroy(T* first, T* last) noexcept {
    if constexpr (!std::is_trivially_destructible_v<T>) {
        for (; first != last; ++first)
            first->~T();
    }
}

}