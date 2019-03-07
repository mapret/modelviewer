#include "Error.hpp"
#include "FrameBuffer.hpp"
#include "GL.hpp"


namespace GL
{
  FrameBuffer::FrameBuffer()
  {
    glGenFramebuffers(1, &name_);
    checkError("FrameBuffer::FrameBuffer()");
  }

  FrameBuffer::FrameBuffer(FrameBuffer&& other)
  {
    name_ = other.name_;
    other.name_ = 0;
  }

  FrameBuffer::~FrameBuffer()
  {
    glDeleteRenderbuffers(1, &name_);
    checkError("FrameBuffer::~FrameBuffer()");
  }

  void FrameBuffer::bind(GLenum target) const
  {
    glBindFramebuffer(target, name_);
  }

  void FrameBuffer::unbind(GLenum target)
  {
    glBindFramebuffer(target, 0);
  }
}
