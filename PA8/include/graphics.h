#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include <vector>

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt, int code);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;


    Object *plane;
    Object *cylinder;
    Object *sphere;
    Object *cube;

    float x = 0, y = 0, z = 0;

    float simTime = 0;

    // Physics
    Physics physicsWorld;
};

#endif /* GRAPHICS_H */
