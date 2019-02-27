#pragma once

#include "math/mat4.hpp"
#include "math/vec3.hpp"


class Camera
{
  public:
    Camera(const vec3& position = vec3(-2, 0, 0), const vec3& direction = vec3(1, 0, 0), const vec3& up = vec3(0, 1, 0), float fov = 90.f, float aspect_ratio = 16/9.f);

    void setVerticalFieldOfView(float fov);
    void setAspectRatio(float aspect_ratio);

    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;

  private:
    vec3 position_;
    vec3 direction_;
    vec3 up_;
    float fov_;
    float aspect_ratio_;
};
