#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"


class Object
{
  public:
    Object(std::string objFile, std::string stextureFile);
    ~Object();

    bool Initialize(std::string objFile);
    void SetVertices();
    void getTextures(std::string textureFile);
    void Update(btRigidBody* rigidBodyID);
    void Render();
    glm::mat4 GetModel();
    void Move(float x, float y, float z, btRigidBody* rigidBodyID);
    void Scale(float size);
    void TranslateBack(float distance);

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

    float angle;
};



#endif /* OBJECT_H */
