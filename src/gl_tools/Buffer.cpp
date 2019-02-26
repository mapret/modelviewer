#include "Buffer.hpp"
#include "Error.hpp"
#include "GL.hpp"


namespace GL
{
  Buffer::Buffer()
  {
    glGenBuffers(1, &name_);
    error("name allocation");
  }

  Buffer::Buffer(Buffer&& other)
  {
    name_ = other.name_;
    other.name_ = 0;
  }

  Buffer::~Buffer()
  {
    glDeleteBuffers(1, &name_);
    error("name deletion");
  }

  void Buffer::bind(GLenum target) const
  {
    glBindBuffer(target, name_);
  }

  void Buffer::unbind(GLenum target)
  {
    glBindBuffer(target, 0);
  }
}
