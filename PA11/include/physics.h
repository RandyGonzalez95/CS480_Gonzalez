#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <vector>
#include "object.h"
#include "string"

class Physics
{

  public:
    Physics();
    ~Physics();

    bool Initialize();
    bool CreateWorld();
    void Pool();
    btDiscreteDynamicsWorld *getWorld();
    btRigidBody* getRigidBody(int index);
    void CreateSphere();
    void CreateCube();
    void CreateTable();
    void CreateTableItem();
    int GetNumItems();


    friend class Graphics;



  private:



    int index, triIndex = 0; // to keep trach which rigidBody we are adding to dynamic world

    // set mass
    btScalar mass;
    // inertia
    btVector3 inertia;

    // Initialize World
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;

    // Physical World
    btDiscreteDynamicsWorld *dynamicsWorld;

    // number of items
    int numItems;

    // Objects
    std::vector<Object*> objects;

    // Collision Shapes
    std::vector<btCollisionShape*> shapes;

    // bt Motion states
    std::vector<btDefaultMotionState*> shapeMS;


    btTriangleMesh *objTriMesh[25];

    std::vector<btRigidBody*> rigidBody;
};

#endif
