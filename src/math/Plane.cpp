#include "Plane.hpp"


Plane::Plane(const vec3& normal, float d)
  : normal_(normal),
    d_(d)
{
}

Plane::Plane(const vec3& normal, const vec3& p)
  : normal_(normal),
    d_(vec3::dot(normal_, p))
{
}

Plane::Plane(const vec3& p1, const vec3& p2, const vec3& p3)
  : normal_(vec3::cross(p2 - p1, p3 - p1).normalized()),
    d_(vec3::dot(normal_, p1))
{
}

void Plane::setNormal(const vec3& normal)
{
  normal_ = normal;
}

void Plane::setDistanceFromOrigin(float d)
{
  d_ = d;
}

void Plane::setDistanceFromOrigin(const vec3& p)
{
  d_ = vec3::dot(normal_, p);
}

const vec3& Plane::getNormal() const
{
  return normal_;
}

float Plane::getDistanceFromOrigin() const
{
  return d_;
}

float Plane::distance(const vec3& p) const
{
  return std::abs(signedDistance(p));
}

float Plane::signedDistance(const vec3& p) const
{
  return vec3::dot(normal_, p) - d_;
}

Line Plane::intersect(const Plane& p1, const Plane& p2)
{
  const vec3& N1 = p1.getNormal();
  const vec3& N2 = p2.getNormal();
  float d1 = p1.getDistanceFromOrigin();
  float d2 = p2.getDistanceFromOrigin();

  //Formulae from http://paulbourke.net/geometry/pointlineplane/
  float determinant = vec3::dot(N1, N1) * vec3::dot(N2, N2) - std::pow(vec3::dot(N1, N2), 2.f);
  float c1 = (d1 * vec3::dot(N2, N2) - d2 * vec3::dot(N1, N2)) / determinant;
  float c2 = (d2 * vec3::dot(N1, N1) - d1 * vec3::dot(N1, N2)) / determinant;
  return Line(c1 * N1 + c2 * N2, vec3::cross(N1, N2));
}
