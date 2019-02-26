#pragma once

#include "noncopyable.hpp"
#include "Types.hpp"


namespace GL
{
  class Texture : public noncopyable
  {
      GLuint name_ = 0;

    public:
      Texture();
      ~Texture();
      Texture(Texture&& other) noexcept;
      Texture& operator=(Texture&& other) noexcept;

      void bind(GLenum target) const;
      static void unbind(GLenum target);
  };
}
