#pragma once

#include "noncopyable.hpp"
#include "Types.hpp"


namespace GL
{
  class FrameBuffer : public noncopyable
  {
    private:
      GLuint name_;

    public:
      FrameBuffer();
      FrameBuffer(FrameBuffer&& other);
      ~FrameBuffer();

      void bind(GLenum target) const;
      static void unbind(GLenum target);
  };
}
