#include "Camera.hpp"
#include "MouseEvent.hpp"
#include "math/math.hpp"
#include <array>


namespace
{
  constexpr float PI = 3.14159265358979323846f;
}

Camera::Camera(const vec3& center, float radius, float latitude, float longitude, float fovy, float aspect_ratio)
  : center_(center),
    radius_(radius),
    latitude_(latitude),
    longitude_(longitude),
    fovy_(fovy),
    aspect_ratio_(aspect_ratio)
{
}

void Camera::reset()
{
  radius_ = 2.f;
  latitude_ = 0.f;
  longitude_ = 0.f;
  fovy_ = 0.8f;
  dirty_bit_ = true;
}

void Camera::setFrustumSidePlanes(const std::array<Plane, 4>& planes, const vec3& center)
{
  Line l1 = Plane::intersect(planes[0], planes[2]); //Horizontal
  Line l2 = Plane::intersect(planes[1], planes[3]); //Vertical
  vec3 pa = l1.closestPoint(l2);
  vec3 pb = l2.closestPoint(l1);

  bool a_closer = vec3::dot(pa - pb, planes[0].getNormal()) > 0;
  if (!a_closer)
    std::swap(pa, pb);

  Line view_line(pa, pb - pa);
  center_ = view_line.closestPoint(center);
  radius_ = (center_ - pa).length();
  dirty_bit_ = true;
}

void Camera::setWindowSize(const vec2u& window_size)
{
  window_size_ = window_size;
  aspect_ratio_ = static_cast<float>(window_size.x) / window_size.y;
  recently_resized_ = true;
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
  return mat4::perspective(fovy_, aspect_ratio_, 0.1f, 1000.f);
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

std::array<Plane, 4> Camera::getFrustumSidePlanes() const
{
  recalculate();
  vec3 forward = (center_ - camera_position_).normalized();
  vec3 left = vec3::cross((center_ - camera_position_).normalized(), camera_up_);
  float tanx = std::tan(fovy_ * aspect_ratio_ / 2.f);
  float tany = std::tan(fovy_ / 2.f);

  std::array<vec3, 4> corners = {
      camera_position_ + forward + left * tanx + camera_up_ * tany,
      camera_position_ + forward - left * tanx + camera_up_ * tany,
      camera_position_ + forward - left * tanx - camera_up_ * tany,
      camera_position_ + forward + left * tanx - camera_up_ * tany
  };

  std::array<Plane, 4> planes;
  for (size_t i = 0; i < corners.size(); i++)
  {
    planes[i] = {corners[i], corners[(i + 1) % corners.size()], camera_position_};
    planes[i].setDistanceFromOrigin(-1000000.f); //TODO: do something different here
  }
  return planes;
}

void Camera::mousePressEvent(const MouseEvent& event)
{
  previous_mouse_position_ = event.position;
}

void Camera::mouseMoveEvent(const MouseEvent& event)
{
  if (recently_resized_)
  {
    recently_resized_ = false;
    mousePressEvent(event);
  }

  vec2i dp = event.position - previous_mouse_position_;
  if (event.buttons & MouseEvent::Buttons::Left)
  {
    constexpr float LAT_MAX = PI / 2.f - 0.1f;
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
  camera_up_ = vec3(std::cos(latitude_ + static_cast<float>(PI / 2.f)) * std::cos(longitude_),
                    std::sin(latitude_ + static_cast<float>(PI / 2.f)),
                    std::cos(latitude_ + static_cast<float>(PI / 2.f)) * std::sin(longitude_));
}
