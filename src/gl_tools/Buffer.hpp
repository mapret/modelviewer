#pragma once

#include "noncopyable.hpp"
#include "Types.hpp"


namespace GL
{
  class Buffer : public noncopyable
  {
    private:
      GLuint name_;

    public:
      Buffer();
      Buffer(Buffer&& other);
      ~Buffer();

      void bind(GLenum target) const;
      static void unbind(GLenum target);
  };
}
