#include "Error.hpp"
#include "GL.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include <stdexcept>


namespace GL
{
  Program::Program(const char* name, const char* vertex_src, const char* fragment_src)
  {
    name_ = glCreateProgram();

    Shader vertex_shader(name, Shader::Type::VERTEX, vertex_src);
    Shader fragment_shader(name, Shader::Type::FRAGMENT, fragment_src);

    vertex_shader.attachTo(name_);
    fragment_shader.attachTo(name_);
    glLinkProgram(name_);

    GLint success;
    glGetProgramiv(name_, GL_LINK_STATUS, &success);
    if (!success)
    {
      GLchar infoLog[1024]{0};
      GLsizei log_length;
      glGetProgramInfoLog(name_, 1024, &log_length, infoLog);
      throw std::runtime_error(std::string("Program::Program(...) (") + name + "): " + infoLog);
    }
    checkError("Program::Program()");
  }

  Program::~Program()
  {
    glDeleteProgram(name_);
    GL::checkError("Program::~Program()");
  }

  Program::Program(Program&& other) noexcept
  {
    name_ = other.name_;
    other.name_ = 0;
  }

  Program& Program::operator=(Program&& other) noexcept
  {
    name_ = other.name_;
    other.name_ = 0;
    return *this;
  }

  void Program::use() const
  {
    glUseProgram(name_);
  }

  void Program::setBool(const char* name, bool value) const
  {
    glUniform1i(getNamedLocation(name), (int) value);
  }

  void Program::setInt(const char* name, int value) const
  {
    glUniform1i(getNamedLocation(name), value);
  }

  void Program::setFloat(const char* name, float value) const
  {
    glUniform1f(getNamedLocation(name), value);
  }

  void Program::setVec2(const char* name, const vec2& value) const
  {
    glUniform2fv(getNamedLocation(name), 1, reinterpret_cast<const float*>(&value));
  }

  void Program::setVec2(const char* name, float x, float y) const
  {
    glUniform2f(getNamedLocation(name), x, y);
  }

  void Program::setVec3(const char* name, const vec3& value) const
  {
    glUniform3fv(getNamedLocation(name), 1, reinterpret_cast<const float*>(&value));
  }

  void Program::setVec3(const char* name, float x, float y, float z) const
  {
    glUniform3f(getNamedLocation(name), x, y, z);
  }

  void Program::setVec4(const char* name, const vec4& value) const
  {
    glUniform4fv(getNamedLocation(name), 1, reinterpret_cast<const float*>(&value));
  }

  void Program::setVec4(const char* name, float x, float y, float z, float w) const
  {
    glUniform4f(getNamedLocation(name), x, y, z, w);
  }

  void Program::setMat3(const char* name, const mat3& mat) const
  {
    glUniformMatrix3fv(getNamedLocation(name), 1, GL_FALSE, &mat[0][0]);
  }

  void Program::setMat4(const char* name, const mat4& mat) const
  {
    glUniformMatrix4fv(getNamedLocation(name), 1, GL_FALSE, mat.data());
  }

  void Program::setMat4(const char* name, const mat4* mat, size_t count) const
  {
    glUniformMatrix4fv(getNamedLocation(name), static_cast<GLsizei> (count), GL_FALSE, mat[0].data());
  }

  bool Program::hasUniformLocation(const char* name) const
  {
    return glGetUniformLocation(name_, name) != -1;
  }

  GLint Program::getNamedLocation(const char* name) const
  {
    GLint ret = glGetUniformLocation(name_, name);
    if (ret == -1)
      throw std::runtime_error(std::string("Uniform variable \"") + name + "\" not found");
    return ret;
  }
}
