#pragma once

#include "vec3.hpp"


class Line
{
  public:
    Line(const vec3& point_on_line = vec3(), const vec3& direction = vec3(1.f, 0.f, 0.f));

    vec3 closestPoint(const Line& l);

  private:
    vec3 p_; //Point on line
    vec3 d_; //Direction
};
