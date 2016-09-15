#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, int &code, bool &toggle, bool &resetKey);
    void Render();

    glm::mat4 GetModel();
    glm::mat4 GetMoonModel();

  private:
    glm::mat4 model;
    glm::mat4 moon_model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float *planetAngle; // Array of planet angles for rotation and orbit
    float *moonAngle;  // Array of moon angles for rotation and orbit
  
};

#endif /* OBJECT_H */
