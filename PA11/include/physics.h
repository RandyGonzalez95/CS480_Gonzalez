#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <vector>
#include "object.h"
#include "string"

class Physics
{
  friend class Graphics;

  public:
    Physics();
    ~Physics();

    bool Initialize();
    bool CreateWorld();
    void Pool();
    btDiscreteDynamicsWorld *getWorld();
    void CreateSphere(std::string objFile, std::string texture, const btVector3 &position);
    void CreateStick();
    void CreateTable();
    void CreateTableItem(std::string objFile, std::string texture);

  private:

    // Dynamics World Variables
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;

    // Physical World
    btDiscreteDynamicsWorld *dynamicsWorld;

    // Objects
    std::vector<Object*> objects;
};

#endif
