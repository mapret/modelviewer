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

  private:
    GL::Program shader_;
};
