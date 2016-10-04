#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object(char *objFile);
    ~Object();

    bool Initialize(char *objFile);
    void SetVertices();
    void Render();
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Geometry;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    // assimp
    Assimp::Importer importer;
    const aiScene *myScene;;


};



#endif /* OBJECT_H */
