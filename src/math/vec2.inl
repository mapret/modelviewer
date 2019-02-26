#include <cmath>
#include <functional>
#include <limits>


template <typename T>
constexpr tvec2<T>::tvec2()
    : x(0), y(0)
{
}

template <typename T>
constexpr tvec2<T>::tvec2(T v)
    : x(v), y(v)
{
}

template <typename T>
constexpr tvec2<T>::tvec2(T _x, T _y)
    : x(_x), y(_y)
{
}

template <typename T>
template<typename U> constexpr tvec2<T>::tvec2(const tvec2<U>& other)
    : x(static_cast<T>(other.x)),
      y(static_cast<T>(other.y))
{
}

template <typename T>
const T& tvec2<T>::operator[](size_t i) const
{
  return *(&x + i);
}

template <typename T>
T& tvec2<T>::operator[](size_t i)
{
  return *(&x + i);
}


//====== Unary arithmetic functions ============================================

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator+=(const tvec2<T>& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator+=(T scalar)
{
  x += scalar;
  y += scalar;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator-=(const tvec2<T>& other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator-=(T scalar)
{
  x -= scalar;
  y -= scalar;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator*=(const tvec2<T>& other)
{
  x *= other.x;
  y *= other.y;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator*=(T scalar)
{
  x *= scalar;
  y *= scalar;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator/=(const tvec2<T>& other)
{
  x /= other.x;
  y /= other.y;
  return *this;
}

template <typename T>
constexpr tvec2<T>& tvec2<T>::operator/=(T scalar)
{
  x /= scalar;
  y /= scalar;
  return *this;
}


//====== Binary arithmetic functions ===========================================

template <typename T>
constexpr tvec2<T> tvec2<T>::operator+(const tvec2<T>& other) const
{
  return tvec2<T>(x + other.x, y + other.y);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator+(T scalar) const
{
  return tvec2<T>(x + scalar, y + scalar);
}

template <typename T>
constexpr tvec2<T> operator+(T scalar, const tvec2<T>& vector)
{
  return vector + scalar;
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator-(const tvec2<T>& other) const
{
  return tvec2<T>(x - other.x, y - other.y);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator-(T scalar) const
{
  return tvec2<T>(x - scalar, y - scalar);
}

template <typename T>
constexpr tvec2<T> operator-(T scalar, const tvec2<T>& vector)
{
  return -vector + scalar;
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator-() const
{
  return tvec2<T>(-x, -y);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator*(const tvec2<T>& other) const
{
  return tvec2<T>(x * other.x, y * other.y);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator*(T scalar) const
{
  return tvec2<T>(x * scalar, y * scalar);
}

template <typename T>
constexpr tvec2<T> operator*(T scalar, const tvec2<T>& vector)
{
  return vector * scalar;
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator/(const tvec2<T>& other) const
{
  return tvec2<T>(x / other.x, y / other.y);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator/(T scalar) const
{
  return tvec2<T>(x / scalar, y / scalar);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::operator%(T scalar) const
{
  return tvec2<T>(x % scalar, y % scalar);
}


//====== Unary geometric functions =============================================

template <typename T>
constexpr T tvec2<T>::lengthSquared() const
{
  return dot(*this, *this);
}

template <typename T>
constexpr T tvec2<T>::length() const
{
  return std::sqrt(lengthSquared());
}

template <typename T>
constexpr void tvec2<T>::normalize()
{
  T l = static_cast<T>(1) / length();
  x *= l;
  y *= l;
}

template <typename T>
constexpr tvec2<T> tvec2<T>::normalized() const
{
  T l = static_cast<T>(1) / length();
  return tvec2<T>(x * l, y * l);
}

template <typename T>
constexpr tvec2<T> tvec2<T>::normalize(const tvec2<T> &vec)
{
  return vec.normalized();
}

template <typename T>
constexpr tvec2<T> tvec2<T>::abs(const tvec2<T>& vec)
{
  return tvec2<T>(std::abs(vec.x), std::abs(vec.y));
}

template <typename T>
constexpr size_t tvec2<T>::hash() const
{
  static_assert(std::is_integral<T>::value, "hash() is only available for vectors with integer types");
  return static_cast<size_t>(x) ^
         (static_cast<size_t>(y) << (std::numeric_limits<size_t>::digits / 2));
}


//====== Binary geometric functions ============================================

template <typename T>
constexpr bool tvec2<T>::operator==(const tvec2<T>& other) const
{
  static_assert(std::is_integral<T>::value, "Operator== is only available for vectors with integer types");
  return x == other.x && y == other.y;
}

template <typename T>
constexpr bool tvec2<T>::operator!=(const tvec2<T>& other) const
{
  return !(*this == other);
}

template <typename T>
constexpr T tvec2<T>::dot(const tvec2<T>& a, const tvec2<T>& b)
{
  return a.x * b.x + a.y * b.y;
}

template <typename T>
constexpr tvec2<T> tvec2<T>::cross(const tvec2<T>& a, const tvec2<T>& b)
{
  return tvec2<T>(a.x * b.y - a.y * b.x);
}

template <typename T>
constexpr T tvec2<T>::distanceSquared(const tvec2<T>& a, const tvec2<T>& b)
{
  return (a - b).lengthSquared();
}

template <typename T>
constexpr T tvec2<T>::distance(const tvec2<T>& a, const tvec2<T>& b)
{
  return (a - b).length();
}

template <typename T>
constexpr tvec2<T> tvec2<T>::max(const tvec2<T>& a, const tvec2<T>& b)
{
  return tvec2<T>(std::max(a.x, b.x), std::max(a.y, b.y));
}

template <typename T>
constexpr tvec2<T> tvec2<T>::min(const tvec2<T>& a, const tvec2<T>& b)
{
  return tvec2<T>(std::min(a.x, b.x), std::min(a.y, b.y));
}


//====== std namespace stuff ===================================================

namespace std
{
  template<typename T>
  struct hash<tvec2<T>>
  {
    size_t operator() (const tvec2<T>& v) const
    {
      return v.hash();
    }
  };
}
