#pragma once

#include <cmath>
#include <cstddef>
#include <ostream>
#include <type_traits>
#include <utility>

namespace ve {

template <template <class> class M, class T, size_t N>
class Vector : public M<T> {
    static_assert(std::is_trivial<M<T>>());
    static_assert(std::is_standard_layout<M<T>>());
    static_assert(sizeof(M<T>) == N * sizeof(T));

public:
    template <class... Ts>
    Vector(Ts&&... args)
        : M<T>(std::forward<Ts>(args)...)
    { }

    template <class U> requires std::is_convertible_v<U, T>
    Vector(const Vector<M, U, N>& other)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] = other[i];
        }
    }

    T& operator[](size_t i)
    {
        return *(reinterpret_cast<T*>(this) + i);
    }

    const T& operator[](size_t i) const
    {
        return *(reinterpret_cast<const T*>(this) + i);
    }

    Vector operator-() const
    {
        Vector result = *this;
        for (size_t i = 0; i < N; i++) {
            result[i] = -result[i];
        }
        return result;
    }

    template <class U> requires std::is_convertible_v<U, T>
    Vector& operator+=(const Vector<M, U, N>& other)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] += other[i];
        }
        return *this;
    }

    template <class U> requires std::is_convertible_v<U, T>
    Vector& operator-=(const Vector<M, U, N>& other)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] -= other[i];
        }
        return *this;
    }

    template <class S> requires std::is_convertible_v<S, T>
    Vector& operator*=(const S& scalar)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] *= scalar;
        }
        return *this;
    }

    template <class S> requires std::is_convertible_v<S, T>
    Vector& operator/=(const S& scalar)
    {
        for (size_t i = 0; i < N; i++) {
            (*this)[i] /= scalar;
        }
        return *this;
    }
};

template <template <class> class M, class U, class V, size_t N>
auto operator+(const Vector<M, U, N>& lhs, const Vector<M, V, N>& rhs)
{
    using R = decltype(std::declval<U>() + std::declval<V>());
    Vector<M, R, N> result = lhs;
    result += rhs;
    return result;
}

template <template <class> class M, class U, class V, size_t N>
auto operator-(const Vector<M, U, N>& lhs, const Vector<M, V, N>& rhs)
{
    using R = decltype(std::declval<U>() - std::declval<V>());
    Vector<M, R, N> result = lhs;
    result -= rhs;
    return result;
}

template <template <class> class M, class T, class S, size_t N>
auto operator*(const Vector<M, T, N>& vector, const S& scalar)
{
    using R = decltype(std::declval<T>() * std::declval<S>());
    Vector<M, R, N> result = vector;
    result *= scalar;
    return result;
}

template <template <class> class M, class T, class S, size_t N>
auto operator*(const S& scalar, const Vector<M, T, N>& vector)
{
    return vector * scalar;
}

template <template <class> class M, class T, class S, size_t N>
auto operator/(const Vector<M, T, N>& vector, const S& scalar)
{
    using R = decltype(std::declval<T>() / std::declval<S>());
    Vector<M, R, N> result = vector;
    result /= scalar;
    return result;
}

template <template <class> class M, class T, size_t N>
T length(const Vector<M, T, N>& vector) requires std::is_arithmetic_v<T>
{
    auto sqsum = T{0};
    for (size_t i = 0; i < N; i++) {
        sqsum += vector[i] * vector[i];
    }
    return std::sqrt(sqsum);
}

template <template <class> class M, class T, size_t N>
Vector<M, T, N> unit(const Vector<M, T, N>& vector)
    requires std::is_arithmetic_v<T>
{
    auto copy = vector;
    auto l = length(copy);
    for (size_t i = 0; i < N; i++) {
        copy[i] /= l;
    }
    return copy;
}

template <template <class> class M, class T, size_t N>
std::ostream& operator<<(std::ostream& output, const Vector<M, T, N>& vector)
{
    static_assert(N > 0);
    output << "[" << vector[0];
    for (size_t i = 1; i < N; i++) {
        output << ", " << vector[i];
    }
    output << "]";
    return output;
}

} // namespace ve
