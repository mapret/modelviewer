#pragma once

#include "gl_tools/Program.hpp"


class Camera;
class Model;

class Renderer
{
  public:
    Renderer();
    void draw(const Model& model, const Camera& camera);

  private:
    GL::Program shader_;
};
