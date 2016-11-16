#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <vector>
#include "object.h"


class Physics
{

  public:
    Physics();
    ~Physics();

    bool Initialize();
    bool CreateWorld();
    void Pinball();
    btDiscreteDynamicsWorld *getWorld();
    btRigidBody* getRigidBody(int index);

    Object *board;
    Object *ball;
    Object *bumper;
    Object *cubeObject;

  private:
    // Initialize World
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;

    // Physical World
    btDiscreteDynamicsWorld *dynamicsWorld;

    // Collision Shapes
    btCollisionShape *table, *ground, *cylinder, *sphere, *rightWall, *leftWall, *topWall, *bottomWall, *cube;
    btTriangleMesh *objTriMesh[3];

    std::vector<btRigidBody*> rigidBody;
};

#endif
