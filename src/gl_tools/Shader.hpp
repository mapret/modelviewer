#pragma once

#include "noncopyable.hpp"
#include "Types.hpp"


namespace GL
{
  class Shader : public noncopyable
  {
    public:
      enum class Type { VERTEX, FRAGMENT, GEOMETRY };

    public:
      Shader(const char* name, Type type, const char* src);
      ~Shader();

      void attachTo(GLuint program_name) const;

    private:
      Type type_;
      GLuint name_;

      const char* getTypeName() const;
  };
}
