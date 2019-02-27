#include "Camera.hpp"


Camera::Camera(const vec3& position, const vec3& direction, const vec3& up, float fov, float aspect_ratio)
  : position_(position),
    direction_(direction),
    up_(up),
    fov_(fov),
    aspect_ratio_(aspect_ratio)
{
}

void Camera::setVerticalFieldOfView(float fov)
{
  fov_ = fov;
}

void Camera::setAspectRatio(float aspect_ratio)
{
  aspect_ratio_ = aspect_ratio;
}

mat4 Camera::getViewMatrix() const
{
  return mat4::lookAt(position_, position_ + direction_, up_);
}

mat4 Camera::getProjectionMatrix() const
{
  return mat4::perspective(fov_, aspect_ratio_, 0.1f, 1000.f);
}
