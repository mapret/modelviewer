#pragma once

#include "math/mat4.hpp"
#include "math/Plane.hpp"
#include "math/vec3.hpp"


class MouseEvent;

class Camera
{
  public:
    Camera(const vec3& center = vec3(), float radius = 2, float latitude = 0, float longitude = 0, float fovy = .8f, float aspect_ratio = 16/9.f);

    void setFrustumSidePlanes(const std::array<Plane, 4>& planes);
    void setWindowSize(const vec2u& window_size);
    void setLastClickedPosition(const vec3& last_clicked);

    const vec3& getPosition() const;
    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;
    vec3 getViewDirection() const;
    vec3 getRayDirectionFromScreenPosition(const vec2i& mouse_position) const;
    std::array<Plane, 4> getFrustumSidePlanes() const;

    void mousePressEvent(const MouseEvent& event);
    void mouseMoveEvent(const MouseEvent& event);
    void mouseWheelEvent(int delta);

  private:
    void recalculate() const;

    vec3 center_;
    float radius_;
    float latitude_;
    float longitude_;
    float fovy_;
    vec2u window_size_;
    float aspect_ratio_;
    vec3 last_clicked_;

    mutable bool dirty_bit_ = true;
    mutable vec3 camera_position_;
    mutable vec3 camera_up_;
    vec2i previous_mouse_position_;
};
