#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

struct vertex
{
  GLfloat position[3];
  GLfloat color[3];
};

class Object
{
  public:
    Object(char *objFile);
    ~Object();
    bool LoadMTL(std::string file, std::string colorInfo);
    bool LoadOBJ(char *obj);
    void Render();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    vertex *Geometry;
    unsigned int *Indices;
    float RGB[3];
    int iSize;
    int vSize;
    GLuint VB;
    GLuint IB;


};



#endif /* OBJECT_H */
