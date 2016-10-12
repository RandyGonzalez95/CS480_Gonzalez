#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"


class Object
{
  public:
    Object(char *objFile, char *textureFile);
    ~Object();

    bool Initialize(char *objFile);
    void SetVertices();
    void getTextures(char* textureFile);
    void Render();
    int GetNumMoons();
    glm::mat4 GetModel();
    glm::mat4 GetMoon(int index);

  private:
    glm::mat4 model;
    glm::mat4 *moonModel;
    std::vector<Vertex> Geometry;
    std::vector<unsigned int> Indices;

    int numMoons;

    GLuint Textures;
    GLuint VB;
    GLuint IB;
    // assimp
    Assimp::Importer importer;
    const aiScene *myScene;
};



#endif /* OBJECT_H */
