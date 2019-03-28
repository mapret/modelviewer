#pragma once

#include "vec3.hpp"


class Line
{
  public:
    Line(const vec3& point_on_line = vec3(), const vec3& direction = vec3(1.f, 0.f, 0.f));

    vec3 closestPoint(const Line& l) const;
    vec3 closestPoint(const vec3& p) const;

  private:
    vec3 p_; //Point on line
    vec3 d_; //Direction
};
