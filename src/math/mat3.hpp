#pragma once

#include "vec2.hpp"
#include "vec3.hpp"
#include <cstddef>


template<typename T>
class tmat3
{
  public:
    constexpr tmat3(): a(1, 0, 0),
                       b(0, 1, 0),
                       c(0, 0, 1){}

    tmat3(T value): a(value, 0, 0),
                    b(0, value, 0),
                    c(0, 0, value) {}

    tmat3(const tvec3<T>& _a,
          const tvec3<T>& _b,
          const tvec3<T>& _c) : a(_a), b(_b), c(_c) {}

    tmat3(T a1, T a2, T a3,
          T b1, T b2, T b3,
          T c1, T c2, T c3):
                            a(a1, a2, a3),
                            b(b1, b2, b3),
                            c(c1, c2, c3){}

    const tvec3<T>& operator[](size_t i) const
    {
      return *(&a + i);
    }

    tvec3<T>& operator[](size_t i)
    {
      return *(&a + i);
    }

    tmat3<T>& operator+=(const tmat3<T>& other)
    {
      a += other.a;
      b += other.b;
      c += other.c;
      return *this;
    }

    tmat3<T>& operator-=(const tmat3<T>& other)
    {
      a -= other.a;
      b -= other.b;
      c -= other.c;
      return *this;
    }

    tmat3<T>& operator*=(const tmat3<T>& other)
    {
      tvec3<T> r1(a.x, b.x, c.x);
      tvec3<T> r2(a.y, b.y, c.y);
      tvec3<T> r3(a.z, b.z, c.z);

      a.x = tvec3<T>::dot(r1, other.a);
      a.y = tvec3<T>::dot(r2, other.a);
      a.z = tvec3<T>::dot(r3, other.a);
      b.x = tvec3<T>::dot(r1, other.b);
      b.y = tvec3<T>::dot(r2, other.b);
      b.z = tvec3<T>::dot(r3, other.b);
      c.x = tvec3<T>::dot(r1, other.c);
      c.y = tvec3<T>::dot(r2, other.c);
      c.z = tvec3<T>::dot(r3, other.c);

      return *this;
    }

    tmat3<T>& operator*=(T scalar)
    {
      a *= scalar;
      b *= scalar;
      c *= scalar;
      return *this;
    }

    tmat3<T>& operator/=(T scalar)
    {
      a /= scalar;
      b /= scalar;
      c /= scalar;
      return *this;
    }

    tmat3<T> operator+(const tmat3<T>& other) const
    {
      return tmat3<T>(a + other.a,
                      b + other.b,
                      c + other.c);
    }

    tmat3<T> operator-(const tmat3<T>& other) const
    {
      return tmat3<T>(a - other.a,
                      b - other.b,
                      c - other.c);
    }

    tmat3<T> operator*(const tmat3<T>& other) const
    {
      tvec3<T> r1(a.x, b.x, c.x);
      tvec3<T> r2(a.y, b.y, c.y);
      tvec3<T> r3(a.z, b.z, c.z);

      return tmat3<T>(
          tvec3<T>::dot(r1, other.a), tvec3<T>::dot(r2, other.a), tvec3<T>::dot(r3, other.a),
          tvec3<T>::dot(r1, other.b), tvec3<T>::dot(r2, other.b), tvec3<T>::dot(r3, other.b),
          tvec3<T>::dot(r1, other.c), tvec3<T>::dot(r2, other.c), tvec3<T>::dot(r3, other.c));
    }

    tvec3<T> operator*(const tvec3<T>& vector) const
    {
      tvec3<T> r1(a.x, b.x, c.x);
      tvec3<T> r2(a.y, b.y, c.y);
      tvec3<T> r3(a.z, b.z, c.z);

      return tvec3<T>(tvec3<T>::dot(r1, vector),
                      tvec3<T>::dot(r2, vector),
                      tvec3<T>::dot(r3, vector));
    }

    tmat3<T> operator*(T scalar) const
    {
      return tmat3<T>(a * scalar,
                      b * scalar,
                      c * scalar);
    }

    tmat3<T> operator/(T scalar) const
    {
      return tmat3<T>(a / scalar,
                      b / scalar,
                      c / scalar);
    }

    tmat3<T> abs() const
    {
      return tmat3<T>(tvec3<T>::abs(a), tvec3<T>::abs(b), tvec3<T>::abs(c));
    }

    tmat3<T> translate(const tvec2<T>& v) const
    {
      tmat3<T> result(*this);
      result.c = a * v.x + b * v.y + c;
      return result;
    }


    tmat3<T> scale(const tvec2<T>& scale) const
    {
      return tmat3<T>(a * scale.x,
                      b * scale.y,
                      c);
    }

    tmat3<T> transpose() const
    {
      return tmat3<T>(a.x, b.x, c.x,
                      a.y, b.y, c.y,
                      a.z, b.z, c.z);
    }

    tmat3<T> inverse() const
    {
      T OneOverDeterminant = 1.f / (
          + a.x * (b.y * c.z - c.y * b.z)
          - b.x * (a.y * c.z - c.y * a.z)
          + c.x * (a.y * b.z - b.y * a.z));

      tmat3<T> Inverse(0);
      Inverse.a.x = +(b.y * c.z - c.y * b.z) * OneOverDeterminant;
      Inverse.b.x = -(b.x * c.z - c.x * b.z) * OneOverDeterminant;
      Inverse.c.x = +(b.x * c.y - c.x * b.y) * OneOverDeterminant;
      Inverse.a.y = -(a.y * c.z - c.y * a.z) * OneOverDeterminant;
      Inverse.b.y = +(a.x * c.z - c.x * a.z) * OneOverDeterminant;
      Inverse.c.y = -(a.x * c.y - c.x * a.y) * OneOverDeterminant;
      Inverse.a.z = +(a.y * b.z - b.y * a.z) * OneOverDeterminant;
      Inverse.b.z = -(a.x * b.z - b.x * a.z) * OneOverDeterminant;
      Inverse.c.z = +(a.x * b.y - b.x * a.y) * OneOverDeterminant;

      return Inverse;
    }

    tmat3<T> rotate(T angle, const tvec3<T>& axis) const
    {
      T c_ = std::cos(angle);
      T s_ = std::sin(angle);
      tvec3<T> temp(axis * (1.f - c_));
      tmat3<T> rotate(0);
      rotate.a.x = c_ + temp.x * axis.x;
      rotate.a.y = 0 + temp.x * axis.y + s_ * axis.z;
      rotate.a.z = 0 + temp.x * axis.z - s_ * axis.y;

      rotate.b.x = 0 + temp.y * axis.x - s_ * axis.z;
      rotate.b.y = c_ + temp.y * axis.y;
      rotate.b.z = 0 + temp.y * axis.z + s_ * axis.x;

      rotate.c.x = 0 + temp.z * axis.x + s_ * axis.y;
      rotate.c.y = 0 + temp.z * axis.y - s_ * axis.x;
      rotate.c.z = c_ + temp.z * axis.z;

      tmat3<T> result;
      result.a = a * rotate.a.x + b * rotate.a.y + c * rotate.a.z;
      result.b = a * rotate.b.x + b * rotate.b.y + c * rotate.b.z;
      result.c = a * rotate.c.x + b * rotate.c.y + c * rotate.c.z;
      return result;
    }

    const T* data() const
    {
      return reinterpret_cast<const T*>(&a);
    }

    tvec3<T> a;
    tvec3<T> b;
    tvec3<T> c;
};

typedef tmat3<float> mat3;
