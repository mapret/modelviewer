#include "math.hpp"
#include <cmath>
#include <functional>
#include <limits>


// unit quaternion
template <typename T>
constexpr tquat<T>::tquat()
  : x(0), y(0), z(0), w(1)
{
}

template <typename T>
constexpr tquat<T>::tquat(T _x, T _y, T _z, T _w)
  : x(_x), y(_y), z(_z), w(_w) 
{
}

template <typename T>
constexpr tquat<T>::tquat(const tvec3<T>& v)
  :  x(v.x), y(v.y), z(v.z), w(T(0)) 
{
}

template <typename T>
constexpr tquat<T> tquat<T>::fromEulerAngles(T _x, T _y, T _z)
{
  _x *= T(0.5);
  _y *= T(0.5);
  _z *= T(0.5);

  T cx = static_cast<T>(cos(_x));
  T cy = static_cast<T>(cos(_y));
  T cz = static_cast<T>(cos(_z));
  T sx = static_cast<T>(sin(_x));
  T sy = static_cast<T>(sin(_y));
  T sz = static_cast<T>(sin(_z));

  tquat<T> q;
  q.x = cx * sy * sz + cy * cz * sx;
  q.y = cx * cz * sy - cy * sx * sz;
  q.z = cx * cy * sz - cz * sx * sy;
  q.w = sx * sy * sz + cx * cy * cz;
  return q;
}

template <typename T>
constexpr tquat<T> tquat<T>::fromEulerAngles(const tvec3<T>& angles)
{
  return fromEulerAngles(angles.x, angles.y, angles.z);
}

template <typename T>
constexpr tquat<T> tquat<T>::fromAngleAxis(T angle, const tvec3<T>& axis)
{
  angle *= T(0.5);
  tquat<T> q;
  T s = static_cast<T>(sin(angle));
  tvec3<T> normed_axis = axis.normalized();
  q.x = normed_axis.x * s;
  q.y = normed_axis.y * s;
  q.z = normed_axis.z * s;
  q.w = static_cast<T>(cos(angle));
  return q;
}

template <typename T>
constexpr tquat<T> tquat<T>::fromAngularVelocity(const tvec3<T>& angular_velocity)
{
  // http://www.euclideanspace.com/physics/kinematics/angularvelocity/
  return tquat<T>(angular_velocity.x, angular_velocity.y, angular_velocity.z, T(0)) * T(0.5);
}

template <typename T>
constexpr tquat<T> tquat<T>::mix(const tquat<T>& lhs, const tquat<T>& rhs, float t)
{
  // Code from glm/gtx/quaternion.inl, shortMix()
  if(t <= 0.f)
    return lhs;
  if(t >= 1.f)
    return rhs;

  T cos = dot(lhs, rhs);
  tquat<T> y2(rhs);
  if(cos < T(0))
  {
    y2 = -rhs;
    cos = -cos;
  }

  T k0, k1;
  if (!math::definitelyLessThan(cos, T(1)))
  {
    k0 = T(1) - t;
    k1 = T(0) + t;
  }
  else
  {
    T sin = std::sqrt(T(1) - cos * cos);
    T angle = std::atan2(sin, cos);
    T one_over_sin = T(1) / sin;
    k0 = std::sin((T(1) - t) * angle) * one_over_sin;
    k1 = std::sin((T(0) + t) * angle) * one_over_sin;
  }

  return tquat<T>(k0 * lhs.x + k1 * y2.x,
                  k0 * lhs.y + k1 * y2.y,
                  k0 * lhs.z + k1 * y2.z,
                  k0 * lhs.w + k1 * y2.w);
}

template <typename T>
constexpr tquat<T> tquat<T>::conjugate(const tquat<T>& q)
{
  return tquat<T>(-q.x, -q.y, -q.z, q.w);
}

template <typename T>
constexpr tquat<T> tquat<T>::inverse(const tquat<T>& q)
{
  return conjugate(q) / normSquared(q);
}

template <typename T>
constexpr tquat<T> tquat<T>::normalized(const tquat<T>& q)
{
  T norm = tquat<T>::norm(q);
  if (norm <= T(0))
    return tquat(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
  T norm_inv = T(1) / norm;
  return tquat<T>(q.x * norm_inv, q.y * norm_inv, q.z * norm_inv, q.w * norm_inv);
}

template <typename T>
constexpr T tquat<T>::dot(const tquat<T>& lhs, const tquat<T>& rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

template <typename T>
constexpr T tquat<T>::norm(const tquat<T>& q)
{
  return std::sqrt(normSquared(q));
}

template <typename T>
constexpr T tquat<T>::normSquared(const tquat<T>& q)
{
  return dot(q,q);
}

template <typename T>
constexpr tvec3<T> tquat<T>::rotate(const tquat<T>& q, const tvec3<T>& v)
{
  return ((q * tquat<T>(v)) * conjugate(q)).xyz();
}

template <typename T>
constexpr tvec3<T> tquat<T>::rotateInverse(const tquat<T>& q, const tvec3<T>& v)
{
  return quat::rotate(q.inverse(), v);
}

template <typename T>
void tquat<T>::normalize()
{
  *this = normalized(*this);
}

template <typename T>
constexpr tquat<T> tquat<T>::inverse() const
{
  return tquat<T>::inverse(*this);
}

template <typename T>
constexpr mat3 tquat<T>::toMat3() const
{
  mat3 m;
  T qxx(x * x);
  T qyy(y * y);
  T qzz(z * z);
  T qxz(x * z);
  T qxy(x * y);
  T qyz(y * z);
  T qwx(w * x);
  T qwy(w * y);
  T qwz(w * z);

  m.a.x = T(1) - T(2) * (qyy + qzz);
  m.a.y = T(2) * (qxy + qwz);
  m.a.z = T(2) * (qxz - qwy);

  m.b.x = T(2) * (qxy - qwz);
  m.b.y = T(1) - T(2) * (qxx + qzz);
  m.b.z = T(2) * (qyz + qwx);

  m.c.x = T(2) * (qxz + qwy);
  m.c.y = T(2) * (qyz - qwx);
  m.c.z = T(1) - T(2) * (qxx + qyy);
  return m;
}

template <typename T>
constexpr mat4 tquat<T>::toMat4() const
{
  return mat4(toMat3());
}

template <typename T>
constexpr tvec3<T> tquat<T>::xyz() const
{
  return tvec3<T>(x, y, z);
}

template <typename T>
constexpr tquat<T> tquat<T>::operator+(const tquat<T>& other) const
{
  return tquat<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

template <typename T>
constexpr tquat<T> tquat<T>::operator-(const tquat<T>& other) const
{
  return tquat<T>(x - other.x, y - other.y, z - other.z, w - other.w);
}

template <typename T>
constexpr tquat<T> tquat<T>::operator-() const
{
  return tquat<T>(-x, -y, -z, -w);
}

template <typename T>
constexpr tquat<T> tquat<T>::operator*(const tquat<T>& other) const
{
  tquat<T> q;
  q.w = w * other.w - x * other.x - y * other.y - z * other.z;
  q.x = x * other.w + w * other.x + y * other.z - z * other.y;
  q.y = w * other.y - x * other.z + y * other.w + z * other.x;
  q.z = w * other.z + x * other.y - y * other.x + z * other.w;
  return q;
}

template <typename T>
constexpr tvec3<T> tquat<T>::operator*(const tvec3<T>& vec) const
{
  tvec3<T> u = tvec3<T>(x, y, z);
  T s = w;
  return u * (tvec3<T>::dot(u, vec) * T(2)) + vec * (s * s - tvec3<T>::dot(u, u)) + tvec3<T>::cross(u, vec) * (T(2.0) * s);
}

template <typename T>
constexpr tquat<T> tquat<T>::operator*(const T scalar) const
{
  return tquat<T>(x * scalar, y * scalar, z * scalar, w * scalar);
}

template <typename T>
constexpr tquat<T> tquat<T>::operator/(const T scalar) const
{
  return tquat<T>(x / scalar, y / scalar, z / scalar, w / scalar);
}

template <typename T>
constexpr tquat<T>& tquat<T>::operator+=(const tquat<T>& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  w += rhs.w;
  return *this;
}

template <typename T>
constexpr tquat<T>& tquat<T>::operator-=(const tquat<T>& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  w -= rhs.w;
  return *this;
}

template <typename T>
constexpr tquat<T>& tquat<T>::operator*=(const tquat<T>& rhs)
{
  tquat<T> q;
  q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
  q.x = x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y;
  q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
  q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
  *this = q;
  return *this;
}

template <typename T>
constexpr tquat<T>& tquat<T>::operator*=(const T rhs)
{
  x *= rhs;
  y *= rhs;
  z *= rhs;
  w *= rhs;
  return *this;
}

template <typename T>
constexpr tquat<T>& tquat<T>::operator/=(const T rhs)
{
  x /= rhs;
  y /= rhs;
  z /= rhs;
  w /= rhs;
  return *this;
}
