#pragma once

#include "gl_tools/Program.hpp"


class Camera;
class Model;
class BoneTransform;

class Renderer
{
  public:
    Renderer();
    void update(const Model& model, BoneTransform& transform, float dt);
    void draw(const Model& model, const BoneTransform& transform, const Camera& camera);
    void setWireframe(bool draw_wireframe);

  private:
    GL::Program shader_;
    bool wireframe_ = false;
};
