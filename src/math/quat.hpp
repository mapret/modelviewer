#pragma once

#include "mat3.hpp"
#include "mat4.hpp"
#include "vec3.hpp"


template<typename T>
class tquat
{
public:
    T x, y, z; // rotation axis
    T w;  // rotation angle

    using type = T;

    constexpr tquat(); // unit quaternion
    constexpr tquat(T x, T y, T z, T w);
    constexpr tquat(const tvec3<T>& v);

    constexpr static tquat<T> fromEulerAngles(T _x, T _y, T _z);
    constexpr static tquat<T> fromEulerAngles(const tvec3<T>& angles);
    constexpr static tquat<T> fromAngleAxis(T angle, const tvec3<T>& axis);
    constexpr static tquat<T> fromAngularVelocity(const tvec3<T>& angular_velocity);
    constexpr static tquat<T> mix(const tquat<T>& lhs, const tquat<T>& rhs, float t);

    constexpr static tquat<T> conjugate(const tquat<T>& q);
    constexpr static tquat<T> inverse(const tquat<T>& q);
    constexpr static tquat<T> normalized(const tquat<T>& q);

    constexpr static T dot(const tquat<T>& lhs, const tquat<T>& rhs);
    constexpr static T norm(const tquat<T>& q);
    constexpr static T normSquared(const tquat<T>& q);

    constexpr static tvec3<T> rotate(const tquat<T>& q, const tvec3<T>& v);
    constexpr static tvec3<T> rotateInverse(const tquat<T>& q, const tvec3<T>& v);

    void normalize();
    constexpr tquat<T> inverse() const;

    constexpr mat3 toMat3() const;
    constexpr mat4 toMat4() const;
    constexpr tvec3<T> xyz() const;

    constexpr tquat<T> operator+(const tquat<T>& other) const;
    constexpr tquat<T> operator-(const tquat<T>& other) const;
    constexpr tquat<T> operator-() const;
    constexpr tquat<T> operator*(const tquat<T>& other) const;
    constexpr tvec3<T> operator*(const tvec3<T>& vec) const;
    constexpr tquat<T> operator*(const T scalar) const;
    constexpr tquat<T> operator/(const T scalar) const;

    constexpr tquat<T>& operator+=(const tquat<T>& other);
    constexpr tquat<T>& operator-=(const tquat<T>& other);
    constexpr tquat<T>& operator*=(const tquat<T>& other);
    constexpr tquat<T>& operator*=(const T scalar);
    constexpr tquat<T>& operator/=(const T scalar);

};

using quat = tquat<float>;

#include "quat.inl"
