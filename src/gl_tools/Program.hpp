#pragma once

#include "noncopyable.hpp"
#include "Types.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/vec4.hpp"


namespace GL
{
  class Program : public noncopyable
  {
      GLuint name_ = 0;

    public:
      Program() = default;
      Program(const char* name, const char* vertex_src, const char* fragment_src);
      Program(Program&& other) noexcept;
      Program& operator=(Program&& other) noexcept;
      ~Program();

      void use() const;
      void setBool(const char* name, bool value) const;
      void setInt(const char* name, int value) const;
      void setFloat(const char* name, float value) const;
      void setVec2(const char* name, const vec2 &value) const;
      void setVec2(const char* name, float x, float y) const;
      void setVec3(const char* name, const vec3 &value) const;
      void setVec3(const char* name, float x, float y, float z) const;
      void setVec4(const char* name, const vec4 &value) const;
      void setVec4(const char* name, float x, float y, float z, float w) const;
      void setMat3(const char* name, const mat3 &mat) const;
      void setMat4(const char* name, const mat4 &mat) const;
      void setMat4(const char* name, const mat4* mat, size_t count) const;
      bool hasUniformLocation(const char* name) const;

    private:
      GLint getNamedLocation(const char* name) const;
  };
}
