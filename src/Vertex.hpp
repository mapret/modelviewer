#pragma once

#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/vec4.hpp"


struct GeometryVertex
{
  vec3 position;
  vec3u bone_indices;
  vec4 vertex_weights;
};

struct GraphicsVertex
{
    vec3 normal;
    vec2 uv;
};
