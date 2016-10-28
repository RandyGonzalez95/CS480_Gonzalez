#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"


class Object
{
  public:
    Object();
    ~Object();

    bool Initialize(char *objFile);
    void SetVertices();
    void getTextures(char* textureFile);
    void Render();
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Geometry;
    std::vector<unsigned int> Indices;

    GLuint Textures;
    GLuint VB;
    GLuint IB;
    // assimp
    Assimp::Importer importer;
    const aiScene *myScene;
};



#endif /* OBJECT_H */
