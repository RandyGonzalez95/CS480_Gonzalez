#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

struct Data
{
  std::string objFile;
  std::string texFile;
  float rAngle;
  float oAngle;
  float distance;
  float size;
  int numberMoons;
};

class Object
{
  public:
    Object();
    ~Object();

    bool Initialize();
    void SetVertices();
    void getTextures();
    void Update(unsigned int dt, bool* code, Data SolarData);
    void Render();
    void RenderSaturn();
    int GetNumMoons();
    void SetData(Data SolarData);
    glm::mat4 GetModel();
    glm::mat4 GetMoon();

  private:
    glm::mat4 model;
    glm::mat4 moonModel;
    std::vector<Vertex> Geometry;
    std::vector<unsigned int> Indices;

    int numMoons;

    GLuint Textures;
    GLuint VB;
    GLuint IB;
    // assimp
    Assimp::Importer importer;
    const aiScene *myScene;

    float *moonAngle;
    float rotateAngle, orbitAngle, distance, size;
    std::string objFile, textureFile;
};



#endif /* OBJECT_H */
