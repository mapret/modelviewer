#include <cmath>
#include <functional>
#include <limits>


template <typename T>
constexpr tvec4<T>::tvec4()
    : x(0), y(0), z(0), w(0)
{
}

template <typename T>
constexpr tvec4<T>::tvec4(T v)
    : x(v), y(v), z(v), w(v)
{
}

template <typename T>
constexpr tvec4<T>::tvec4(T _x, T _y, T _z, T _w)
    : x(_x), y(_y), z(_z), w(_w)
{
}

template <typename T>
constexpr tvec4<T>::tvec4(const tvec3<T>& v, T _w)
    : x(v.x), y(v.y), z(v.z), w(_w)
{
}

template <typename T>
template<typename U> constexpr tvec4<T>::tvec4(const tvec4<U>& other)
    : x(static_cast<T>(other.x)),
      y(static_cast<T>(other.y)),
      z(static_cast<T>(other.z)),
      w(static_cast<T>(other.w))
{
}

template <typename T>
constexpr tvec3<T> tvec4<T>::xyz() const
{
  return tvec3<T>(x, y, z);
}

template <typename T>
const T& tvec4<T>::operator[](size_t i) const
{
  return *(&x + i);
}

template <typename T>
T& tvec4<T>::operator[](size_t i)
{
  return *(&x + i);
}


//====== Unary arithmetic functions ============================================

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator+=(const tvec4<T>& other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator+=(T scalar)
{
  x += scalar;
  y += scalar;
  z += scalar;
  w += scalar;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator-=(const tvec4<T>& other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator-=(T scalar)
{
  x -= scalar;
  y -= scalar;
  z -= scalar;
  w -= scalar;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator*=(const tvec4<T>& other)
{
  x *= other.x;
  y *= other.y;
  z *= other.z;
  w *= other.w;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator*=(T scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator/=(const tvec4<T>& other)
{
  x /= other.x;
  y /= other.y;
  z /= other.z;
  w /= other.w;
  return *this;
}

template <typename T>
constexpr tvec4<T>& tvec4<T>::operator/=(T scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  z /= scalar;
  return *this;
}


//====== Binary arithmetic functions ===========================================

template <typename T>
constexpr tvec4<T> tvec4<T>::operator+(const tvec4<T>& other) const
{
  return tvec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator+(T scalar) const
{
  return tvec4<T>(x + scalar, y + scalar, z + scalar, w + scalar);
}

template <typename T>
constexpr tvec4<T> operator+(T scalar, const tvec4<T>& vector)
{
  return vector + scalar;
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator-(const tvec4<T>& other) const
{
  return tvec4<T>(x - other.x, y - other.y, z - other.z, w + other.w);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator-(T scalar) const
{
  return tvec4<T>(x - scalar, y - scalar, z - scalar, w - scalar);
}

template <typename T>
constexpr tvec4<T> operator-(T scalar, const tvec4<T>& vector)
{
  return -vector + scalar;
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator-() const
{
  return tvec4<T>(-x, -y, -z, -w);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator*(const tvec4<T>& other) const
{
  return tvec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator*(T scalar) const
{
  return tvec4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
}

template <typename T>
constexpr tvec4<T> operator*(T scalar, const tvec4<T>& vector)
{
  return vector * scalar;
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator/(const tvec4<T>& other) const
{
  return tvec4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator/(T scalar) const
{
  return tvec4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::operator%(T scalar) const
{
  return tvec4<T>(x % scalar, y % scalar, z % scalar, w % scalar);
}


//====== Unary geometric functions =============================================

template <typename T>
constexpr T tvec4<T>::lengthSquared() const
{
  return dot(*this, *this);
}

template <typename T>
constexpr T tvec4<T>::length() const
{
  return std::sqrt(lengthSquared());
}

template <typename T>
constexpr void tvec4<T>::normalize()
{
  T l = static_cast<T>(1) / length();
  x *= l;
  y *= l;
  z *= l;
  w *= l;
}

template <typename T>
constexpr tvec4<T> tvec4<T>::normalized() const
{
  T l = static_cast<T>(1) / length();
  return tvec4<T>(x * l, y * l, z * l, w * l);
}

template <typename T>
constexpr tvec4<T> tvec4<T>::normalize(const tvec4<T> &vec)
{
  return vec.normalized();
}

template <typename T>
constexpr tvec4<T> tvec4<T>::abs(const tvec4<T>& vec)
{
  return tvec4<T>(std::abs(vec.x), std::abs(vec.y), std::abs(vec.z), std::abs(vec.w));
}

template <typename T>
constexpr size_t tvec4<T>::hash() const
{
  static_assert(std::is_integral<T>::value, "hash() is only available for vectors with integer types");
  return (static_cast<size_t>(y) << (std::numeric_limits<size_t>::digits * 0 / 4)) ^
         (static_cast<size_t>(y) << (std::numeric_limits<size_t>::digits * 1 / 4)) ^
         (static_cast<size_t>(y) << (std::numeric_limits<size_t>::digits * 2 / 4)) ^
         (static_cast<size_t>(z) << (std::numeric_limits<size_t>::digits * 3 / 4));
}


//====== Binary geometric functions ============================================

template <typename T>
constexpr bool tvec4<T>::operator==(const tvec4<T>& other) const
{
  static_assert(std::is_integral<T>::value, "Operator== is only available for vectors with integer types");
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <typename T>
constexpr bool tvec4<T>::operator!=(const tvec4<T>& other) const
{
  return !(*this == other);
}

template <typename T>
constexpr T tvec4<T>::dot(const tvec4<T>& a, const tvec4<T>& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T>
constexpr T tvec4<T>::distanceSquared(const tvec4<T>& a, const tvec4<T>& b)
{
  return (a - b).lengthSquared();
}

template <typename T>
constexpr T tvec4<T>::distance(const tvec4<T>& a, const tvec4<T>& b)
{
  return (a - b).length();
}

template <typename T>
constexpr tvec4<T> tvec4<T>::max(const tvec4<T>& a, const tvec4<T>& b)
{
  return tvec4<T>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}

template <typename T>
constexpr tvec4<T> tvec4<T>::min(const tvec4<T>& a, const tvec4<T>& b)
{
  return tvec4<T>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}


//====== std namespace stuff ===================================================

namespace std
{
  template<typename T>
  struct hash<tvec4<T>>
  {
      size_t operator() (const tvec4<T>& v) const
      {
        return v.hash();
      }
  };
}
