#pragma once

#include <functional>
#include <vector>


namespace math
{
  namespace
  {
    template <typename T>
    constexpr T EPSILON() { return T(1e-4); }
  }

  template<typename T>
  bool almostEqual(T a, T b)
  {
    static_assert(std::is_floating_point<T>::value, "math::almostEqual can only be used for floating point numbers");
    //https://stackoverflow.com/a/253874
    return std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * EPSILON<T>();
  }

  template<typename T>
  bool definitelyLessThan(T a, T b)
  {
    static_assert(std::is_floating_point<T>::value, "math::definitelyLessThan can only be used for floating point numbers");
    //https://stackoverflow.com/a/253874
    return (b - a) > std::max(std::abs(a), std::abs(b)) * EPSILON<T>();
  }

  template<typename T>
  T toRadiants(const T degrees)
  {
    return degrees * static_cast<T>(0.01745329251994329576923690768489);
  }

  template<typename T>
  T toDegrees(const T radiant)
  {
    return radiant * static_cast<T>(57.295779513082320876798154814105);
  }

  template<typename T>
  T mapRange(const T input, const T in_start, const T in_end, const T out_start, const T out_end)
  {
    return (((input - in_start) * (out_end - out_start)) / (in_end - in_start)) + out_start;
  }

  template<typename T, typename U>
  U mapRange(const T input, const T in_start, const T in_end, const U& out_start, const U& out_end)
  {
    T n = T(1) / (in_end - in_start);
    return out_end * ((input - in_start) * n) + out_start * ((in_end - input) * n);
  }
}
