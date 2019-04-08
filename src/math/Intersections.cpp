#include "Intersections.hpp"


float Intersections::rayTriangle(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& ray_origin, const vec3& ray_direction)
{
  //Code adapted from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
  vec3 E1 = p2 - p1;
  vec3 E2 = p3 - p1;
  vec3 S = ray_origin - p1;
  vec3 S1 = vec3::cross(ray_direction, E2);
  vec3 S2 = vec3::cross(S, E1);
  float denum = 1.f / vec3::dot(S1, E1);
  float t = vec3::dot(S2, E2) * denum;
  float b1 = vec3::dot(S1, S) * denum;
  float b2 = vec3::dot(S2, ray_direction) * denum;
  if (b1 < 0 || b1 > 1)
    return std::numeric_limits<float>::infinity();
  if (b2 < 0 || b1 + b2 > 1)
    return std::numeric_limits<float>::infinity();
  if (t < 0)
    return std::numeric_limits<float>::infinity();
  return t;
}
