#pragma once

#include <cstddef>
#include <cstdint>


template<typename T>
class tvec3
{
  public:
    T x;
    T y;
    T z;

    constexpr tvec3();
    constexpr explicit tvec3(T v);
    constexpr tvec3(T x, T y, T z);
    template<typename U> constexpr explicit tvec3(const tvec3<U>& other);

    const T& operator[](size_t i) const;
    T& operator[](size_t i);

    //Unary arithmetic functions
    constexpr tvec3<T>& operator+=(const tvec3<T>& other);
    constexpr tvec3<T>& operator+=(T scalar);
    constexpr tvec3<T>& operator-=(const tvec3<T>& other);
    constexpr tvec3<T>& operator-=(T scalar);
    constexpr tvec3<T>& operator*=(const tvec3<T>& other);
    constexpr tvec3<T>& operator*=(T scalar);
    constexpr tvec3<T>& operator/=(const tvec3<T>& other);
    constexpr tvec3<T>& operator/=(T scalar);

    //Binary arithmetic functions
    constexpr tvec3<T> operator+(const tvec3<T>& other) const;
    constexpr tvec3<T> operator+(T scalar) const;
    constexpr tvec3<T> operator-(const tvec3<T>& other) const;
    constexpr tvec3<T> operator-(T scalar) const;
    constexpr tvec3<T> operator-() const;
    constexpr tvec3<T> operator*(const tvec3<T>& other) const;
    constexpr tvec3<T> operator*(T scalar) const;
    constexpr tvec3<T> operator/(const tvec3<T>& other) const;
    constexpr tvec3<T> operator/(T scalar) const;
    constexpr tvec3<T> operator%(T scalar) const;

    //Unary geometric functions
    constexpr T lengthSquared() const;
    constexpr T length() const;
    constexpr void normalize();
    constexpr tvec3<T> normalized() const;
    constexpr static tvec3<T> normalize(const tvec3<T> &vec);
    constexpr static tvec3<T> abs(const tvec3<T>& vec);
    constexpr size_t hash() const;

    //Binary geometric functions
    constexpr bool operator==(const tvec3<T>& other) const;
    constexpr bool operator!=(const tvec3<T>& other) const;
    constexpr static T dot(const tvec3<T>& a, const tvec3<T>& b);
    constexpr static tvec3<T> cross(const tvec3<T>& a, const tvec3<T>& b);
    constexpr static T distanceSquared(const tvec3<T>& a, const tvec3<T>& b);
    constexpr static T distance(const tvec3<T>& a, const tvec3<T>& b);
    constexpr static tvec3<T> max(const tvec3<T>& a, const tvec3<T>& b);
    constexpr static tvec3<T> min(const tvec3<T>& a, const tvec3<T>& b);
};

using vec3f = tvec3<float>;
using vec3d = tvec3<double>;
using vec3i = tvec3<int32_t>;
using vec3u = tvec3<uint32_t>;
using vec3l = tvec3<int64_t>;
using vec3L = tvec3<uint64_t>;
using vec3 = vec3f;

#include "vec3.inl"
