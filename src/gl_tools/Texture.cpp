#include "Error.hpp"
#include "GL.hpp"
#include "Texture.hpp"


namespace GL
{
  Texture::Texture()
  {
    glGenTextures(1, &name_);
    GL::checkError("Texture::Texture()");
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &name_);
    GL::checkError("Texture::~Texture");
  }

  Texture::Texture(GL::Texture&& other) noexcept
  {
    name_ = other.name_;
    other.name_ = 0;
  }

  Texture& Texture::operator=(Texture&& other) noexcept
  {
    glDeleteTextures(1, &name_);
    name_ = other.name_;
    other.name_ = 0;
    return *this;
  }

  void Texture::bind(GLenum target) const
  {
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_2D, name_);
  }

  void Texture::unbind(GLenum target)
  {
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}
