#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"


class Object
{
  public:
    Object(char *objFile);
    ~Object();
    void Render();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    //vertex *Geometry;
    //unsigned int *Indices;
    //float RGB[3];
    //int iSize;
    //int vSize;
    GLuint VB;
    GLuint IB;


};



#endif /* OBJECT_H */
