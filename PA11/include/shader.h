#ifndef SHADER_H
#define SHADER_H

#include "graphics_headers.h"
#include <iostream>

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    std::string readShaderFile(const char* fileName);
    bool AddShader(GLenum ShaderType, bool flag);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
