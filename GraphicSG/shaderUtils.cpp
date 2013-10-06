#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <vr/shaderUtils.h>
#include <fstream>

using namespace vr;

GLuint vr::loadShaderFromString(const std::string& source, GLuint shader_type)
{

  // Create a vertex shader
  GLuint shader_id = glCreateShaderObjectARB(shader_type);
  CheckErrorsGL("glCreateShaderObjectARB");

  // Attach the source to the shader
  const char *cstr = source.c_str();
  glShaderSourceARB(shader_id, 1, &cstr, NULL);
  if (!CheckErrorsGL(std::string("glShaderSourceARB: ") + source))
    return 0;
  

  // Tell the driver to compile the shader source
  glCompileShaderARB(shader_id);
  if (!CheckErrorsGL("glCompileShaderARB"))
    return 0;

  GLint params;

  // Was the compilation successful?
  glGetObjectParameterivARB(shader_id, GL_OBJECT_COMPILE_STATUS_ARB,
    &params);

  if (params == GL_FALSE) {
    char log[256];
    GLsizei length;
    glGetInfoLogARB(shader_id,
      256,
      &length,
      log);
    log[length]='\0';
    std::cerr << "Error compiling shader: " << log << std::endl;
    return 0;
  }

  return shader_id;

}

GLuint vr::loadShader(const std::string& path, GLuint shader_type)
{
  // Create a vertex shader
  GLuint shader_id = glCreateShaderObjectARB(shader_type);
  CheckErrorsGL(std::string("glCreateShaderObjectARB: ") + path);

  // Open the shader text file
  std::ifstream in;
  in.open(path.c_str(), std::ios::in);
  if (!in.is_open())
    return 0;

  std::string source;
  std::string line;

  while(!in.eof()) {
    std::getline(in, line);
    source += line;
    source += "\n";
  }

  GLuint id = loadShaderFromString( source, shader_type);
  if (!id)
  {
    std::cerr << "Error when compiling shader file: '" << path << "\'" << std::endl;
    return 0;
  }

  return id;
}

bool vr::checkLinkStatus( GLuint programID )
{
  GLint success;

  glGetObjectParameterivARB(programID, GL_OBJECT_LINK_STATUS_ARB, &success);
  if (!success) {
    char log[256];
    GLsizei length;
    glGetInfoLogARB(programID,
      255,
      &length,
      log);
    log[length]='\0';
    std::cerr << "Error linking program: " << log << std::endl;
    return false;
  }

  return true;
}
