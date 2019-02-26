#include <cmath>
#include <functional>
#include <limits>


template <typename T>
constexpr tvec3<T>::tvec3()
    : x(0), y(0), z(0)
{
}

template <typename T>
constexpr tvec3<T>::tvec3(T v)
    : x(v), y(v), z(v)
{
}

template <typename T>
constexpr tvec3<T>::tvec3(T _x, T _y, T _z)
    : x(_x), y(_y), z(_z)
{
}

template <typename T>
template<typename U> constexpr tvec3<T>::tvec3(const tvec3<U>& other)
    : x(static_cast<T>(other.x)),
      y(static_cast<T>(other.y)),
      z(static_cast<T>(other.z))
{
}

template <typename T>
const T& tvec3<T>::operator[](size_t i) const
{
  return *(&x + i);
}

template <typename T>
T& tvec3<T>::operator[](size_t i)
{
  return *(&x + i);
}


//====== Unary arithmetic functions ============================================

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator+=(const tvec3<T>& other)
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator+=(T scalar)
{
  x += scalar;
  y += scalar;
  z += scalar;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator-=(const tvec3<T>& other)
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator-=(T scalar)
{
  x -= scalar;
  y -= scalar;
  z -= scalar;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator*=(const tvec3<T>& other)
{
  x *= other.x;
  y *= other.y;
  z *= other.z;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator*=(T scalar)
{
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator/=(const tvec3<T>& other)
{
  x /= other.x;
  y /= other.y;
  z /= other.z;
  return *this;
}

template <typename T>
constexpr tvec3<T>& tvec3<T>::operator/=(T scalar)
{
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}


//====== Binary arithmetic functions ===========================================

template <typename T>
constexpr tvec3<T> tvec3<T>::operator+(const tvec3<T>& other) const
{
  return tvec3<T>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator+(T scalar) const
{
  return tvec3<T>(x + scalar, y + scalar, z + scalar);
}

template <typename T>
constexpr tvec3<T> operator+(T scalar, const tvec3<T>& vector)
{
  return vector + scalar;
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator-(const tvec3<T>& other) const
{
  return tvec3<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator-(T scalar) const
{
  return tvec3<T>(x - scalar, y - scalar, z - scalar);
}

template <typename T>
constexpr tvec3<T> operator-(T scalar, const tvec3<T>& vector)
{
  return -vector + scalar;
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator-() const
{
  return tvec3<T>(-x, -y, -z);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator*(const tvec3<T>& other) const
{
  return tvec3<T>(x * other.x, y * other.y, z * other.z);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator*(T scalar) const
{
  return tvec3<T>(x * scalar, y * scalar, z * scalar);
}

template <typename T>
constexpr tvec3<T> operator*(T scalar, const tvec3<T>& vector)
{
  return vector * scalar;
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator/(const tvec3<T>& other) const
{
  return tvec3<T>(x / other.x, y / other.y, z / other.z);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator/(T scalar) const
{
  return tvec3<T>(x / scalar, y / scalar, z / scalar);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::operator%(T scalar) const
{
  return tvec3<T>(x % scalar, y % scalar, z % scalar);
}


//====== Unary geometric functions =============================================

template <typename T>
constexpr T tvec3<T>::lengthSquared() const
{
  return dot(*this, *this);
}

template <typename T>
constexpr T tvec3<T>::length() const
{
  return std::sqrt(lengthSquared());
}

template <typename T>
constexpr void tvec3<T>::normalize()
{
  T l = static_cast<T>(1) / length();
  x *= l;
  y *= l;
  z *= l;
}

template <typename T>
constexpr tvec3<T> tvec3<T>::normalized() const
{
  T l = static_cast<T>(1) / length();
  return tvec3<T>(x * l, y * l, z * l);
}

template <typename T>
constexpr tvec3<T> tvec3<T>::normalize(const tvec3<T> &vec)
{
  return vec.normalized();
}

template <typename T>
constexpr tvec3<T> tvec3<T>::abs(const tvec3<T>& vec)
{
  return tvec3<T>(std::abs(vec.x), std::abs(vec.y), std::abs(vec.z));
}

template <typename T>
constexpr size_t tvec3<T>::hash() const
{
  static_assert(std::is_integral<T>::value, "hash() is only available for vectors with integer types");
  return static_cast<size_t>(x) ^
      (static_cast<size_t>(y) << (std::numeric_limits<size_t>::digits / 3)) ^
      (static_cast<size_t>(z) << (std::numeric_limits<size_t>::digits * 2 / 3));
}


//====== Binary geometric functions ============================================

template <typename T>
constexpr bool tvec3<T>::operator==(const tvec3<T>& other) const
{
  static_assert(std::is_integral<T>::value, "Operator== is only available for vectors with integer types");
  return x == other.x && y == other.y && z == other.z;
}

template <typename T>
constexpr bool tvec3<T>::operator!=(const tvec3<T>& other) const
{
  return !(*this == other);
}

template <typename T>
constexpr T tvec3<T>::dot(const tvec3<T>& a, const tvec3<T>& b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
constexpr tvec3<T> tvec3<T>::cross(const tvec3<T>& a, const tvec3<T>& b)
{
  return tvec3<T>(a.y * b.z - b.y * a.z,
                  a.z * b.x - b.z * a.x,
                  a.x * b.y - b.x * a.y);
}

template <typename T>
constexpr T tvec3<T>::distanceSquared(const tvec3<T>& a, const tvec3<T>& b)
{
  return (a - b).lengthSquared();
}

template <typename T>
constexpr T tvec3<T>::distance(const tvec3<T>& a, const tvec3<T>& b)
{
  return (a - b).length();
}

template <typename T>
constexpr tvec3<T> tvec3<T>::max(const tvec3<T>& a, const tvec3<T>& b)
{
  return tvec3<T>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

template <typename T>
constexpr tvec3<T> tvec3<T>::min(const tvec3<T>& a, const tvec3<T>& b)
{
  return tvec3<T>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}


//====== std namespace stuff ===================================================

namespace std
{
  template<typename T>
  struct hash<tvec3<T>>
  {
      size_t operator() (const tvec3<T>& v) const
      {
        return v.hash();
      }
  };
}
