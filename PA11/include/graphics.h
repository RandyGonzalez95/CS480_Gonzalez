#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include <vector>

#include "physics.h"

class Graphics
{
  friend class Physics;

  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height, bool flag);
    void Update(unsigned int dt, bool codes[]);
    void SetCamera(bool codes[]);
    void PlayGame(bool codes[]);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    // Location of MVP matrix
    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    // Light Sources
    GLint m_LightPosition;
    GLint m_AmbientProduct;
    GLint m_DiffuseProduct;
    GLint m_SpecularProduct;
    GLfloat m_shininess;

    // Camera Position
    float x = 0, y = 0, z = 0;

    // Simulation Time
    float simTime = 0;

    // Lights
    float light = 1.0f;
    float light2 = 0.5f;

    // Physics World
    Physics *physicsWorld;
};

#endif /* GRAPHICS_H */
