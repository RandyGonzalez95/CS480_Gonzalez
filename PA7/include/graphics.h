#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "SolarSystem.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height, char* configFile);
    void Update( unsigned int dt, int code);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;


    SolarSystem *MilkyWay;
};

#endif /* GRAPHICS_H */
