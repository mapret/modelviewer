#include "Camera.hpp"
#include "MouseEvent.hpp"
#include "math/math.hpp"


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

void Camera::setWindowSize(const vec2u& window_size)
{
  window_size_ = window_size;
  aspect_ratio_ = static_cast<float>(window_size.x) / window_size.y;
}

void Camera::setLastClickedPosition(const vec3& last_clicked)
{
  last_clicked_ = last_clicked;
}

const vec3& Camera::getPosition() const
{
  recalculate();
  return camera_position_;
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

vec3 Camera::getViewDirection() const
{
  recalculate();
  return vec3::normalize(center_ - camera_position_);
}

vec3 Camera::getRayDirectionFromScreenPosition(const vec2i& mouse_position) const
{
  mat4 inv_vp = (getProjectionMatrix() * getViewMatrix()).inverse();
  vec4 screen_pos(2.f * mouse_position.x / window_size_.x - 1.f, 2.f * (window_size_.y - mouse_position.y) / window_size_.y - 1.f, 1.f, 1.f);
  vec4 world_pos = inv_vp * screen_pos;
  return world_pos.xyz().normalized();
}

void Camera::mousePressEvent(const MouseEvent& event)
{
  previous_mouse_position_ = event.position;
}

void Camera::mouseMoveEvent(const MouseEvent& event)
{
  vec2i dp = event.position - previous_mouse_position_;
  if (event.buttons & MouseEvent::Buttons::Left)
  {
    constexpr float LAT_MAX = static_cast<float>(M_PI_2) - 0.1f;
    latitude_ = std::clamp(latitude_ + dp.y / 100.f, -LAT_MAX, LAT_MAX);
    longitude_ += dp.x / 100.f;
  }
  else if (event.buttons & MouseEvent::Buttons::Middle)
  {
    float distance_from_camera = vec3::distance(camera_position_, last_clicked_);
    vec3 r1 = getRayDirectionFromScreenPosition(previous_mouse_position_) * distance_from_camera;
    vec3 r2 = getRayDirectionFromScreenPosition(event.position) * distance_from_camera;
    float distance = vec3::distance(r1, r2);
    vec3 side = vec3::cross((center_ - camera_position_).normalized(), camera_up_);
    vec2 dp_norm = vec2(dp);
    if (math::definitelyLessThan(0.f, dp_norm.length()))
      dp_norm.normalize();
    center_ -= side * dp_norm.x * distance - camera_up_ * dp_norm.y * distance;
  }

  previous_mouse_position_ = event.position;
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
  camera_up_ = vec3(std::cos(latitude_ + static_cast<float>(M_PI_2)) * std::cos(longitude_),
                    std::sin(latitude_ + static_cast<float>(M_PI_2)),
                    std::cos(latitude_ + static_cast<float>(M_PI_2)) * std::sin(longitude_));
}
