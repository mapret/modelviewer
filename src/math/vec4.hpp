#pragma once

#include <cstddef>
#include <cstdint>


template<typename T>
class tvec4
{
  public:
    T x;
    T y;
    T z;
    T w;

    constexpr tvec4();
    constexpr explicit tvec4(T v);
    constexpr tvec4(T x, T y, T z, T w);
    constexpr tvec4(const tvec3<T>& v, T w);
    template<typename U> constexpr explicit tvec4(const tvec4<U>& other);

    constexpr tvec3<T> xyz() const;
    const T& operator[](size_t i) const;
    T& operator[](size_t i);

    //Unary arithmetic functions
    constexpr tvec4<T>& operator+=(const tvec4<T>& other);
    constexpr tvec4<T>& operator+=(T scalar);
    constexpr tvec4<T>& operator-=(const tvec4<T>& other);
    constexpr tvec4<T>& operator-=(T scalar);
    constexpr tvec4<T>& operator*=(const tvec4<T>& other);
    constexpr tvec4<T>& operator*=(T scalar);
    constexpr tvec4<T>& operator/=(const tvec4<T>& other);
    constexpr tvec4<T>& operator/=(T scalar);

    //Binary arithmetic functions
    constexpr tvec4<T> operator+(const tvec4<T>& other) const;
    constexpr tvec4<T> operator+(T scalar) const;
    constexpr tvec4<T> operator-(const tvec4<T>& other) const;
    constexpr tvec4<T> operator-(T scalar) const;
    constexpr tvec4<T> operator-() const;
    constexpr tvec4<T> operator*(const tvec4<T>& other) const;
    constexpr tvec4<T> operator*(T scalar) const;
    constexpr tvec4<T> operator/(const tvec4<T>& other) const;
    constexpr tvec4<T> operator/(T scalar) const;
    constexpr tvec4<T> operator%(T scalar) const;

    //Unary geometric functions
    constexpr T lengthSquared() const;
    constexpr T length() const;
    constexpr void normalize();
    constexpr tvec4<T> normalized() const;
    constexpr static tvec4<T> normalize(const tvec4<T> &vec);
    constexpr static tvec4<T> abs(const tvec4<T>& vec);
    constexpr size_t hash() const;

    //Binary geometric functions
    constexpr bool operator==(const tvec4<T>& other) const;
    constexpr bool operator!=(const tvec4<T>& other) const;
    constexpr static T dot(const tvec4<T>& a, const tvec4<T>& b);
    constexpr static T distanceSquared(const tvec4<T>& a, const tvec4<T>& b);
    constexpr static T distance(const tvec4<T>& a, const tvec4<T>& b);
    constexpr static tvec4<T> max(const tvec4<T>& a, const tvec4<T>& b);
    constexpr static tvec4<T> min(const tvec4<T>& a, const tvec4<T>& b);
};

using vec4f = tvec4<float>;
using vec4d = tvec4<double>;
using vec4i = tvec4<int32_t>;
using vec4u = tvec4<uint32_t>;
using vec4l = tvec4<int64_t>;
using vec4L = tvec4<uint64_t>;
using vec4 = vec4f;

#include "vec4.inl"
