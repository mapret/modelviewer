#pragma once

#include "gl_tools/Texture.hpp"
#include "gl_tools/Types.hpp"
#include "math/vec3.hpp"


struct Material
{
  vec3 color_diffuse = { 0.5f, 0.5f, 0.5f };
  vec3 color_specular = { 1.f, 1.f, 1.f };
  GL::Texture texture;
};
