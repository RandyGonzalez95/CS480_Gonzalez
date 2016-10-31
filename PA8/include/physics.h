#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <vector>

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

  private:
    // Initialize World
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;

    // Physical World
    btDiscreteDynamicsWorld *dynamicsWorld;

    // Collision Shapes
    btCollisionShape *plane, *cylinder, *sphere;
    btTriangleMesh *objTriMesh[3];

    std::vector<btRigidBody*> rigidBody;
};

#endif
