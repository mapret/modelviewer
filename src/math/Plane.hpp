#pragma once

#include "Line.hpp"
#include "vec3.hpp"


class Plane
{
  public:
    Plane(const vec3& normal = vec3(1.f, 0.f, 0.f), float d = 0.f);
    Plane(const vec3& normal, const vec3& p);
    Plane(const vec3& p1, const vec3& p2, const vec3& p3);

    void setNormal(const vec3& normal);
    void setDistanceFromOrigin(float d);
    void setDistanceFromOrigin(const vec3& p);
    const vec3& getNormal() const;
    float getDistanceFromOrigin() const;

    float distance(const vec3& p) const;
    float signedDistance(const vec3& p) const;
    static Line intersect(const Plane& p1, const Plane& p2);

  private:
    //Stored in Hesse normal form (https://en.wikipedia.org/wiki/Hesse_normal_form)
    vec3 normal_; //Normal vector
    float d_ = 0; //Distance from origin
};
