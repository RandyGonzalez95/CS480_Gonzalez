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
    void CreateSphere(btScalar mass, btVector3 inertia);
    void CreateCube(btScalar mass, btVector3 inertia);
    void CreateTable(btScalar mass, btVector3 inertia);
    void CreatePaddle(btScalar mass, btVector3 inertia, const btVector3 &position);
    void CreatePaddle2(btScalar mass, btVector3 inertia, const btVector3 &position);
    void CreateBumper(btScalar mass, btVector3 inertia, const btVector3 &position);
    void CreateGlass(btScalar mass, btVector3 inertia);


    friend class Graphics;



  private:

    // Objects
    Object *board, *ball, *bumper, *cubeObject, *leftPaddle, *rightPaddle, *capsule, *capsule2;

    int index; // to keep trach which rigidBody we are adding to dynamic world

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
