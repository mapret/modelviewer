#pragma once

#include "math/mat4.hpp"
#include "math/vec3.hpp"


class MouseEvent;

class Camera
{
  public:
    Camera(const vec3& center = vec3(), float radius = 2, float latitude = 0, float longitude = 0, float fov = 90.f, float aspect_ratio = 16/9.f);

    void setVerticalFieldOfView(float fov);
    void setAspectRatio(float aspect_ratio);

    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;

    void mousePressEvent(const MouseEvent& event);
    void mouseMoveEvent(const MouseEvent& event);
    void mouseWheelEvent(int delta);

  private:
    void recalculate() const;

    vec3 center_;
    float radius_;
    float latitude_;
    float longitude_;
    float fov_;
    float aspect_ratio_;

    mutable bool dirty_bit_ = true;
    mutable vec3 camera_position_;
    mutable vec3 camera_up_;
    vec2i previous_mouse_position_;
};
