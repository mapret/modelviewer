#pragma once

#include "noncopyable.hpp"
#include "Types.hpp"


namespace GL
{
  class VertexArray : public noncopyable
  {
    private:
      GLuint name_;

    public:
      VertexArray();
      VertexArray(VertexArray&& other);
      ~VertexArray();

      void bind() const;
      static void unbind();
  };
}
