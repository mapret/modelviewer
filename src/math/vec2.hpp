#pragma once

#include <cstddef>
#include <cstdint>


template<typename T>
class tvec2
{
  public:
    T x;
    T y;

    constexpr tvec2();
    constexpr explicit tvec2(T v);
    constexpr tvec2(T x, T y);
    template<typename U> constexpr explicit tvec2(const tvec2<U>& other);

    const T& operator[](size_t i) const;
    T& operator[](size_t i);

    //Unary arithmetic functions
    constexpr tvec2<T>& operator+=(const tvec2<T>& other);
    constexpr tvec2<T>& operator+=(T scalar);
    constexpr tvec2<T>& operator-=(const tvec2<T>& other);
    constexpr tvec2<T>& operator-=(T scalar);
    constexpr tvec2<T>& operator*=(const tvec2<T>& other);
    constexpr tvec2<T>& operator*=(T scalar);
    constexpr tvec2<T>& operator/=(const tvec2<T>& other);
    constexpr tvec2<T>& operator/=(T scalar);

    //Binary arithmetic functions
    constexpr tvec2<T> operator+(const tvec2<T>& other) const;
    constexpr tvec2<T> operator+(T scalar) const;
    constexpr tvec2<T> operator-(const tvec2<T>& other) const;
    constexpr tvec2<T> operator-(T scalar) const;
    constexpr tvec2<T> operator-() const;
    constexpr tvec2<T> operator*(const tvec2<T>& other) const;
    constexpr tvec2<T> operator*(T scalar) const;
    constexpr tvec2<T> operator/(const tvec2<T>& other) const;
    constexpr tvec2<T> operator/(T scalar) const;
    constexpr tvec2<T> operator%(T scalar) const;

    //Unary geometric functions
    constexpr T lengthSquared() const;
    constexpr T length() const;
    constexpr void normalize();
    constexpr tvec2<T> normalized() const;
    constexpr static tvec2<T> normalize(const tvec2<T> &vec);
    constexpr static tvec2<T> abs(const tvec2<T>& vec);
    constexpr size_t hash() const;

    //Binary geometric functions
    constexpr bool operator==(const tvec2<T>& other) const;
    constexpr bool operator!=(const tvec2<T>& other) const;
    constexpr static T dot(const tvec2<T>& a, const tvec2<T>& b);
    constexpr static tvec2<T> cross(const tvec2<T>& a, const tvec2<T>& b);
    constexpr static T distanceSquared(const tvec2<T>& a, const tvec2<T>& b);
    constexpr static T distance(const tvec2<T>& a, const tvec2<T>& b);
    constexpr static tvec2<T> max(const tvec2<T>& a, const tvec2<T>& b);
    constexpr static tvec2<T> min(const tvec2<T>& a, const tvec2<T>& b);
};

using vec2f = tvec2<float>;
using vec2d = tvec2<double>;
using vec2i = tvec2<int32_t>;
using vec2u = tvec2<uint32_t>;
using vec2l = tvec2<int64_t>;
using vec2L = tvec2<uint64_t>;
using vec2 = vec2f;

#include "vec2.inl"
