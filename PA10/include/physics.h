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
    friend class Graphics;



  private:
    Object *board;
    Object *ball;
    Object *bumper;
    Object *cubeObject;
    Object *leftPaddle;
    Object *rightPaddle;
    Object *capsule;
    Object *capsule2;
    // Initialize World
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;

    // Physical World
    btDiscreteDynamicsWorld *dynamicsWorld;

    // Collision Shapes
    btCollisionShape *table, *glass, *cylinder, *sphere, *left, *right, *cube, *capsuleShape, *capsuleShape2;
    btTriangleMesh *objTriMesh[3];

    std::vector<btRigidBody*> rigidBody;
};

#endif
