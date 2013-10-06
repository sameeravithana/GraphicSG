
#ifndef shaderUtils_h_
#define shaderUtils_h_

#include <GL/gl.h>
#include <iostream>
#include <string>
#include <vr/glErrorUtil.h>

#define STRINGIFY(A) #A

namespace vr
{


  /**
  Function that will load and create a Shader object 
  \param path - full path to an text file containing the shader code
  \param shader_type - Can be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
  \returns 0 on failure, a valid Shader object if successful.
  */
  GLuint loadShader(const std::string& path, GLuint shader_type);

  /**
  Function that will load and create a Shader object from a string
  \param path - text containing the shadercode
  \param shader_type - Can be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
  \returns 0 on failure, a valid Shader object if successful.
  */
  GLuint loadShaderFromString(const std::string& shaderCode, GLuint shader_type);

  bool checkLinkStatus( GLuint programID );
}

#endif
