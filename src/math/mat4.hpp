#pragma once

#include "mat3.hpp"
#include "vec3.hpp"
#include "vec4.hpp"


template<typename T>
class tmat4
{
  public:
    constexpr tmat4(): a(1, 0, 0, 0),
                       b(0, 1, 0, 0),
                       c(0, 0, 1, 0),
                       d(0, 0, 0, 1) {}

    tmat4(T value): a(value, 0, 0, 0),
                    b(0, value, 0, 0),
                    c(0, 0, value, 0),
                    d(0, 0, 0, value) {}

    tmat4(const tmat3<T>& m): a(m.a.x, m.a.y, m.a.z, 0),
                              b(m.b.x, m.b.y, m.b.z, 0),
                              c(m.c.x, m.c.y, m.c.z, 0),
                              d(0, 0, 0, 1) {}

    tmat4(const tvec4<T>& _a,
          const tvec4<T>& _b,
          const tvec4<T>& _c,
          const tvec4<T>& _d) : a(_a), b(_b), c(_c), d(_d) {}

    tmat4(T a1, T a2, T a3, T a4,
          T b1, T b2, T b3, T b4,
          T c1, T c2, T c3, T c4,
          T d1, T d2, T d3, T d4): a(a1, a2, a3, a4),
                                   b(b1, b2, b3, b4),
                                   c(c1, c2, c3, c4),
                                   d(d1, d2, d3, d4) {}

    tmat4<T>& operator+=(const tmat4<T>& other)
    {
      a += other.a;
      b += other.b;
      c += other.c;
      d += other.d;
      return *this;
    }

    tmat4<T>& operator-=(const tmat4<T>& other)
    {
      a -= other.a;
      b -= other.b;
      c -= other.c;
      d -= other.d;
      return *this;
    }

    tmat4<T>& operator*=(const tmat4<T>& other)
    {
      tvec4<T> r1(a.x, b.x, c.x, d.x);
      tvec4<T> r2(a.y, b.y, c.y, d.y);
      tvec4<T> r3(a.z, b.z, c.z, d.z);
      tvec4<T> r4(a.w, b.w, c.w, d.w);

      a.x = tvec4<T>::dot(r1, other.a);
      a.y = tvec4<T>::dot(r2, other.a);
      a.z = tvec4<T>::dot(r3, other.a);
      a.w = tvec4<T>::dot(r4, other.a);
      b.x = tvec4<T>::dot(r1, other.b);
      b.y = tvec4<T>::dot(r2, other.b);
      b.z = tvec4<T>::dot(r3, other.b);
      b.w = tvec4<T>::dot(r4, other.b);
      c.x = tvec4<T>::dot(r1, other.c);
      c.y = tvec4<T>::dot(r2, other.c);
      c.z = tvec4<T>::dot(r3, other.c);
      c.w = tvec4<T>::dot(r4, other.c);
      d.x = tvec4<T>::dot(r1, other.d);
      d.y = tvec4<T>::dot(r2, other.d);
      d.z = tvec4<T>::dot(r3, other.d);
      d.w = tvec4<T>::dot(r4, other.d);

      return *this;
    }

    tmat4<T>& operator*=(T scalar)
    {
      a *= scalar;
      b *= scalar;
      c *= scalar;
      d *= scalar;
      return *this;
    }

    tmat4<T>& operator/=(T scalar)
    {
      a /= scalar;
      b /= scalar;
      c /= scalar;
      d /= scalar;
      return *this;
    }

    tmat4<T> operator+(const tmat4<T>& other) const
    {
      return tmat4<T>(a + other.a,
                      b + other.b,
                      c + other.c,
                      d + other.d);
    }

    tmat4<T> operator-(const tmat4<T>& other) const
    {
      return tmat4<T>(a - other.a,
                      b - other.b,
                      c - other.c,
                      c - other.c);
    }

    tmat4<T> operator*(const tmat4<T>& other) const
    {
      tvec4<T> r1(a.x, b.x, c.x, d.x);
      tvec4<T> r2(a.y, b.y, c.y, d.y);
      tvec4<T> r3(a.z, b.z, c.z, d.z);
      tvec4<T> r4(a.w, b.w, c.w, d.w);

      return tmat4<T>(
          tvec4<T>::dot(r1, other.a), tvec4<T>::dot(r2, other.a),
          tvec4<T>::dot(r3, other.a), tvec4<T>::dot(r4, other.a),
          tvec4<T>::dot(r1, other.b), tvec4<T>::dot(r2, other.b),
          tvec4<T>::dot(r3, other.b), tvec4<T>::dot(r4, other.b),
          tvec4<T>::dot(r1, other.c), tvec4<T>::dot(r2, other.c),
          tvec4<T>::dot(r3, other.c), tvec4<T>::dot(r4, other.c),
          tvec4<T>::dot(r1, other.d), tvec4<T>::dot(r2, other.d),
          tvec4<T>::dot(r3, other.d), tvec4<T>::dot(r4, other.d));
    }

    tvec4<T> operator*(const tvec4<T>& vector) const
    {
      tvec4<T> r1(a.x, b.x, c.x, d.x);
      tvec4<T> r2(a.y, b.y, c.y, d.y);
      tvec4<T> r3(a.z, b.z, c.z, d.z);
      tvec4<T> r4(a.w, b.w, c.w, d.w);

      return tvec4<T>(tvec4<T>::dot(r1, vector),
                      tvec4<T>::dot(r2, vector),
                      tvec4<T>::dot(r3, vector),
                      tvec4<T>::dot(r4, vector));
    }

    tmat4<T> operator*(T scalar) const
    {
      return tmat4<T>(a * scalar,
                      b * scalar,
                      c * scalar,
                      d * scalar);
    }

    tmat4<T> operator/(T scalar) const
    {
      return tmat4<T>(a / scalar,
                      b / scalar,
                      c / scalar,
                      d / scalar);
    }

    tmat4<T> translate(const tvec3<T>& v) const
    {
      tmat4<T> result(*this);
      result.d = a * v.x + b * v.y + c * v.z + d;
      return result;
    }

    tmat4<T> rotate(T angle, const tvec3<T>& axis) const
    {
      T c_ = std::cos(angle);
      T s_ = std::sin(angle);
      tvec3<T> temp(axis * (1.f - c_));
      tmat4<T> rotate(0);
      rotate.a.x = c_ + temp.x * axis.x;
      rotate.a.y = 0 + temp.x * axis.y + s_ * axis.z;
      rotate.a.z = 0 + temp.x * axis.z - s_ * axis.y;

      rotate.b.x = 0 + temp.y * axis.x - s_ * axis.z;
      rotate.b.y = c_ + temp.y * axis.y;
      rotate.b.z = 0 + temp.y * axis.z + s_ * axis.x;

      rotate.c.x = 0 + temp.z * axis.x + s_ * axis.y;
      rotate.c.y = 0 + temp.z * axis.y - s_ * axis.x;
      rotate.c.z = c_ + temp.z * axis.z;

      tmat4<T> result;
      result.a = a * rotate.a.x + b * rotate.a.y + c * rotate.a.z;
      result.b = a * rotate.b.x + b * rotate.b.y + c * rotate.b.z;
      result.c = a * rotate.c.x + b * rotate.c.y + c * rotate.c.z;
      result.d = d;
      return result;
    }

    tmat4<T> scale(const tvec3<T>& scale) const
    {
      return tmat4<T>(a * scale.x,
                      b * scale.y,
                      c * scale.z,
                      d);
    }

    tmat4<T> transpose() const
    {
      return tmat4<T>(a.x, b.x, c.x, d.x,
                      a.y, b.y, c.y, d.y,
                      a.z, b.z, c.z, d.z,
                      a.w, b.w, c.w, d.w);
    }

    tmat4<T> inverse() const
    {
      T Coef00 = c.z * d.w - d.z * c.w;
      T Coef02 = b.z * d.w - d.z * b.w;
      T Coef03 = b.z * c.w - c.z * b.w;

      T Coef04 = c.y * d.w - d.y * c.w;
      T Coef06 = b.y * d.w - d.y * b.w;
      T Coef07 = b.y * c.w - c.y * b.w;

      T Coef08 = c.y * d.z - d.y * c.z;
      T Coef10 = b.y * d.z - d.y * b.z;
      T Coef11 = b.y * c.z - c.y * b.z;

      T Coef12 = c.x * d.w - d.x * c.w;
      T Coef14 = b.x * d.w - d.x * b.w;
      T Coef15 = b.x * c.w - c.x * b.w;

      T Coef16 = c.x * d.z - d.x * c.z;
      T Coef18 = b.x * d.z - d.x * b.z;
      T Coef19 = b.x * c.z - c.x * b.z;

      T Coef20 = c.x * d.y - d.x * c.y;
      T Coef22 = b.x * d.y - d.x * b.y;
      T Coef23 = b.x * c.y - c.x * b.y;

      tvec4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
      tvec4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
      tvec4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
      tvec4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
      tvec4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
      tvec4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

      tvec4<T> Vec0(b.x, a.x, a.x, a.x);
      tvec4<T> Vec1(b.y, a.y, a.y, a.y);
      tvec4<T> Vec2(b.z, a.z, a.z, a.z);
      tvec4<T> Vec3(b.w, a.w, a.w, a.w);

      tvec4<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
      tvec4<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
      tvec4<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
      tvec4<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

      tvec4<T> SignA(+1, -1, +1, -1);
      tvec4<T> SignB(-1, +1, -1, +1);
      tmat4<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

      tvec4<T> Row0(Inverse.a.x, Inverse.b.x, Inverse.c.x, Inverse.d.x);

      tvec4<T> Dot0(a * Row0);
      T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

      T OneOverDeterminant = 1.f / Dot1;

      return Inverse * OneOverDeterminant;
    }

    static tmat4<T> lookAt(const tvec3<T>& position, const tvec3<T>& look_at,
                       const tvec3<T>& up)
    {
      tvec3<T> const f((look_at - position).normalized());
      tvec3<T> const s(tvec3<T>::cross(f, up).normalized());
      tvec3<T> const u(tvec3<T>::cross(s, f));

      tmat4<T> Result(1);
      Result.a.x = s.x;
      Result.b.x = s.y;
      Result.c.x = s.z;
      Result.a.y = u.x;
      Result.b.y = u.y;
      Result.c.y = u.z;
      Result.a.z = -f.x;
      Result.b.z = -f.y;
      Result.c.z = -f.z;
      Result.d.x = -tvec3<T>::dot(s, position);
      Result.d.y = -tvec3<T>::dot(u, position);
      Result.d.z = tvec3<T>::dot(f, position);
      return Result;
    }

    static tmat4<float> perspective(float fov, float ratio, float znear, float zfar)
    {
      float const tanHalfFov = std::tan(fov / 2.f);

      tmat4<float> Result(0);
      Result.a.x = 1.f / (ratio * tanHalfFov);
      Result.b.y = 1.f / (tanHalfFov);
      Result.c.z = -(zfar + znear) / (zfar - znear);
      Result.c.w = -1.f;
      Result.d.z = -2.f * zfar * znear / (zfar - znear);
      return Result;
    }

    static tmat4<float> ortho(float left, float right, float bottom, float top, float near, float far)
    {
      tmat4<float> Result(1.f);
      Result.a.x = 2.f / (right - left);
      Result.b.y = 2.f / (top - bottom);
      Result.c.z = -2.f / (far - near);
      Result.d.x = -(right + left) / (right - left);
      Result.d.y = -(top + bottom) / (top - bottom);
      Result.d.z = -(far + near) / (far - near);
      return Result;
    }

    const T* data() const
    {
      return reinterpret_cast<const T*>(&a);
    }

    tvec4<T> a;
    tvec4<T> b;
    tvec4<T> c;
    tvec4<T> d;
};

typedef tmat4<float> mat4;
