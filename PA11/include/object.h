#ifndef OBJECT_H
#define OBJECT_H

#include "graphics_headers.h"
#include <iostream>

struct Vertex
{
  GLfloat position[3];
  GLfloat uv[2];
  GLfloat normal[3];
};

class Object
{
  friend class Physics;

  public:
    Object(); // Constructor
    ~Object(); // Destructor

    void CreateObject(std::string objFile, std::string textureFile, btTriangleMesh *triMesh); // Create the object
    bool Initialize(std::string objFile); // Initialize the object
    void SetVertices(btTriangleMesh *triMesh); // Set vertices of object
    void SetTexture(std::string textureFile); // Set texture of object
    void Update(); // Update the object
    void SetLocation(float, Object *cueBall); // set stick relative to ball
    void unrenderPoolStick(); // Unrender the pool stick
    void ResetCue(); // Reset cue ball
    void Render(); // Render the object

    // Data member gets
    glm::mat4 GetModel(); // Get Model
    btRigidBody* getRigidBody(); // Get rigid body
    btTransform  getTrans(); // Get object trans

    bool madeIn = false;

  private:
    glm::mat4 model;
    std::vector<Vertex> Geometry;
    std::vector<unsigned int> Indices;

    // Texture members
    GLuint Textures;
    GLuint VB;
    GLuint IB;

    // Assimp members
    Assimp::Importer importer;
    const aiScene *myScene;

    // Bullet members
    btCollisionShape *shape;
    btMotionState *motionState;
    btRigidBody *rigidBody;
    btTriangleMesh *objTriMesh;
    btScalar mass;
    btVector3 inertia;
};

#endif /* OBJECT_H */
