#include "Error.hpp"
#include "GL.hpp"
#include <stdexcept>
#include <string>


namespace
{
  const char* getErrorString(GLenum error_code)
  {
    switch (error_code)
    {
      case GL_STACK_OVERFLOW:                return "stack overflow";
      case GL_STACK_UNDERFLOW:               return "stack underflow";
      case GL_INVALID_ENUM:                  return "invalid enum";
      case GL_INVALID_VALUE:                 return "invalud value";
      case GL_INVALID_OPERATION:             return "invalid operation";
      case GL_OUT_OF_MEMORY:                 return "out of memory";
      case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
      default:                               return "unknown error";
    }
  }
}

namespace GL
{
  void checkError(const std::string_view at)
  {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
      throw std::runtime_error(std::string(getErrorString(error)) + " (" + std::to_string(error) + ") at " + std::string(at) + "\n");
    }
  }
}
