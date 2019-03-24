#pragma once

#include "vec3.hpp"


namespace Intersections
{
  float rayTriangle(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& ray_origin, const vec3& ray_direction);
};
