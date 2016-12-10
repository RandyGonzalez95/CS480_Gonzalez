#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <btBulletDynamicsCommon.h>


class Object
{
  public:
    Object();
    ~Object();

    void CreateObject(std::string objFile, std::string textureFile, btTriangleMesh *triMesh);
    bool Initialize(std::string objFile);
    void SetVertices(btTriangleMesh *triMesh);
    void SetTexture(std::string textureFile);
    void Update(btRigidBody* rigidBodyID);
    void Render();
    glm::mat4 GetModel();

    // Bullet variables
    btCollisionShape *shape;
    btMotionState *motionState;
    btRigidBody *rigidBody;
    btTriangleMesh *objTriMesh;
    btScalar mass;
    btVector3 inertia;
    
  private:
    glm::mat4 model;
    std::vector<Vertex> Geometry;
    std::vector<unsigned int> Indices;

    GLuint Textures;
    GLuint VB;
    GLuint IB;


    // Assimp
    Assimp::Importer importer;
    const aiScene *myScene;
};

#endif /* OBJECT_H */
