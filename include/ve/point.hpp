#pragma once

#include "ve/vector.hpp"

#include <cstddef>
#include <type_traits>

namespace ve {

template <template <class> class M, class T, size_t N>
class Point : public M<T> {
    static_assert(sizeof(M<T>) == N * sizeof(T));

public:
    T& operator[](size_t i)
    {
        return *(reinterpret_cast<T*>(this) + i);
    }

    const T& operator[](size_t i) const
    {
        return *(reinterpret_cast<const T*>(this) + i);
    }

    template <class U> requires std::is_convertible_v<U, T>
    Point& operator+=(const Vector<M, U, N>& vector)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] += vector[i];
        }
        return *this;
    }

    template <class U> requires std::is_convertible_v<U, T>
    Point& operator-=(const Vector<M, U, N>& vector)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] -= vector[i];
        }
        return *this;
    }
};

template <template <class> class M, class U, class V, size_t N>
auto operator+(const Point<M, U, N>& point, const Vector<M, V, N>& vector)
{
    Point<M, std::common_type_t<U, V>, N> result = point;
    result += vector;
    return point;
}

template <template <class> class M, class U, class V, size_t N>
auto operator-(const Point<M, U, N>& point, const Vector<M, V, N>& vector)
{
    Point<M, std::common_type_t<U, V>, N> result = point;
    result -= vector;
    return point;
}

template <template <class> class M, class U, class V, size_t N>
auto operator-(const Point<M, U, N>& lhs, const Point<M, V, N>& rhs)
{
    Vector<M, std::common_type_t<U, V>, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

template <template <class> class M, class U, class V, size_t N>
auto distance(const Point<M, U, N>& lhs, const Point<M, V, N>& rhs)
{
    return (lhs - rhs).length();
}

} // namespace ve
