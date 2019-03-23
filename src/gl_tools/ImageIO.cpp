#include "Error.hpp"
#include "GL.hpp"
#include "ImageIO.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


GL::Texture GL::loadImage(const std::filesystem::path& path, vec2u& size)
{
  int width, height, num_components;
  unsigned char* img_data = stbi_load(path.string().c_str(), &width, &height, &num_components, 0);
  if (!img_data)
    throw std::runtime_error("Failed to load \"" + path.string() + "\"");
  size.x = static_cast<typeof(size.x)>(width);
  size.y = static_cast<typeof(size.y)>(height);
  auto texture = uploadTextureToGPU(img_data, width, height, num_components);
  stbi_image_free(img_data);
  return texture;
}

GL::Texture GL::uploadTextureToGPU(const uint8_t* img_data, int width, int height, int num_components)
{
  GLenum format = GL_RGB;
  if (num_components == 1)      format = GL_R;
  else if (num_components == 2) format = GL_RG;
  else if (num_components == 3) format = GL_RGB;
  else if (num_components == 4) format = GL_RGBA;
  else throw std::runtime_error("GL::uploadTextureToGPU(): Too many color components");

  GL::Texture texture;
  texture.bind(GL_TEXTURE0);
  glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), width, height, 0, format, GL_UNSIGNED_BYTE, img_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  GL::checkError("GL::uploadTextureToGPU");
  return texture;
}
