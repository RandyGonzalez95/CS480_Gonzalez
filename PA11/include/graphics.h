#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "camera.h"
#include "shader.h"
#include "physics.h"

class Graphics
{
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

    // Camera Position// Debugging cube
    float x = 0, y = 0, z = 0;

    float xPos = 0, yPos = 0, zPos = 0;

    // Force on ball
    float xForce = -90, zForce = 0;

    bool shot = false;

    bool lpositiveX = true;
    bool lpositiveZ = true;

    bool rpositiveX = true;
    bool rpositiveZ = true;


    // Simulation Time
    float simTime = 0;

    // Lights
    float light = 1.0f;
    float light2 = 0.5f;

    float theta_y = 0;

    // Physics World
    Physics *physicsWorld;

    bool outputCue = false;
};

#endif /* GRAPHICS_H */
