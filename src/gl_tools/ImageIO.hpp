#pragma once

#include "Texture.hpp"
#include "math/vec2.hpp"
#include <filesystem>


namespace GL
{
  Texture loadImage(const std::filesystem::path& path, vec2u& size);
  Texture uploadTextureToGPU(const uint8_t* img_data, int width, int height, int num_components);
};
