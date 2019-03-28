#include "Line.hpp"


Line::Line(const vec3& point_on_line, const vec3& direction)
  : p_(point_on_line),
    d_(direction)
{
}

vec3 Line::closestPoint(const Line& l) const
{
  //Formulae from http://paulbourke.net/geometry/pointlineplane/
  float mua = (vec3::dot(p_ - l.p_, l.d_) * vec3::dot(l.d_, d_) - vec3::dot(p_ - l.p_, d_) * vec3::dot(l.d_, l.d_)) /
              (vec3::dot(d_, d_) * vec3::dot(l.d_, l.d_) - vec3::dot(l.d_, d_) * vec3::dot(l.d_, d_));
  return p_ + mua * d_;
}

vec3 Line::closestPoint(const vec3& p) const
{
  //Formulate from http://paulbourke.net/geometry/pointlineplane/
  float u = vec3::dot(p - p_, d_) / d_.lengthSquared();
  return p_ + d_ * u;
}
