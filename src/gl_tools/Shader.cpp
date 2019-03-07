#include "Shader.hpp"
#include "GL.hpp"
#include "Error.hpp"
#include <sstream>
#include <cassert>


namespace GL
{
  Shader::Shader(const char* name, Type type, const char* src)
    : type_(type)
  {
    switch (type_)
    {
      case Type::VERTEX:
        name_ = glCreateShader(GL_VERTEX_SHADER);
        break;
      case Type::FRAGMENT:
        name_ = glCreateShader(GL_FRAGMENT_SHADER);
        break;
      case Type::GEOMETRY:
        name_ = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    }

    const char* sources[2] = {"#version 420 core\n", nullptr};
    sources[1] = src;
    glShaderSource(name_, 2, sources, NULL);
    glCompileShader(name_);

    GLint success;
    glGetShaderiv(name_, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      GLchar infoLog[1024]{0};
      glGetShaderInfoLog(name_, 1024, NULL, infoLog);
      throw std::runtime_error(std::string("Shader::Shader(): compilation error (") + name + " " + getTypeName() + "): " + infoLog);
    }
    GL::checkError(std::string("Shader::Shader(): shader-name='") + name + "'");
  }

  Shader::~Shader()
  {
    glDeleteShader(name_);
    GL::checkError("Shader::~Shader()");
  }

  void Shader::attachTo(GLuint program_name) const
  {
    glAttachShader(program_name, name_);
  }

  const char* Shader::getTypeName() const
  {
    switch (type_)
    {
      case Type::VERTEX:
        return "vertex shader";
      case Type::FRAGMENT:
        return "fragment shader";
      case Type::GEOMETRY:
        return "geometry shader";
    }
    return nullptr;
  }
}
