#include "Camera.hpp"


Camera::Camera(const vec3& center, float radius, float latitude, float longitude, float fov, float aspect_ratio)
  : center_(center),
    radius_(radius),
    latitude_(latitude),
    longitude_(longitude),
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
  recalculate();
  return mat4::lookAt(camera_position_, center_, camera_up_);
}

mat4 Camera::getProjectionMatrix() const
{
  recalculate();
  return mat4::perspective(fov_, aspect_ratio_, 0.1f, 1000.f);
}

void Camera::mousePressEvent(const vec2i& mouse_position)
{
  previous_mouse_position_ = mouse_position;
}

void Camera::mouseMoveEvent(const vec2i& mouse_position)
{
  constexpr static float LAT_MAX = static_cast<float>(M_PI_2) - 0.1f;
  vec2i dp = mouse_position - previous_mouse_position_;
  latitude_ = std::clamp(latitude_ + dp.y / 100.f, -LAT_MAX, LAT_MAX);
  longitude_ += dp.x / 100.f;

  previous_mouse_position_ = mouse_position;
  dirty_bit_ = true;
}

void Camera::mouseWheelEvent(const int delta)
{
  constexpr static float ZOOM_FACTOR = 1.2f;
  constexpr static float MIN_ZOOM = 0.01f;

  radius_ *= delta < 0 ? ZOOM_FACTOR : 1.f / ZOOM_FACTOR;
  if (radius_ < MIN_ZOOM)
    radius_ *= ZOOM_FACTOR;

  dirty_bit_ = true;
}

void Camera::recalculate() const
{
  if (!dirty_bit_)
    return;
  dirty_bit_ = false;

  camera_position_ = center_ + radius_ *
      vec3(std::cos(latitude_) * std::cos(longitude_),
           std::sin(latitude_),
           std::cos(latitude_) * std::sin(longitude_));
  camera_up_ = vec3(0, 1, 0);
}
