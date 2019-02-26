#include "GL.hpp"
#include "VertexArray.hpp"
#include "Error.hpp"


namespace GL
{
  VertexArray::VertexArray()
  {
    glGenVertexArrays(1, &name_);
    error("vertex array allocation");
  }

  VertexArray::VertexArray(VertexArray&& other)
  {
    name_ = other.name_;
    other.name_ = 0;
  }

  VertexArray::~VertexArray()
  {
    glDeleteVertexArrays(1, &name_);
    error("vertex array deletion");
  }

  void VertexArray::bind() const
  {
    glBindVertexArray(name_);
  }

  void VertexArray::unbind()
  {
    glBindVertexArray(0);
  }
}
