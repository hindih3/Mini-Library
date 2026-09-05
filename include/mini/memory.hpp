#pragma once
#include <type_traits>

namespace mini {
    
template <class T>
T* allocate(size_t n) {
    return (n == 0) ? nullptr : static_cast<T*>(::operator new(sizeof(T) * n));
}

template <class T>
void deallocate(T* ptr) noexcept {
    ::operator delete(ptr);
}

template <class T, class... Args>
void construct(T* ptr, Args&&... args) {
    ::new (static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
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