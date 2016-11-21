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
    void Pinball();
    btDiscreteDynamicsWorld *getWorld();
    btRigidBody* getRigidBody(int index);
    void CreateSphere();
    void CreateCube();
    void CreateTable();
    void CreateTableItem(std::string objectFile, std::string textureFile, Object* obj, btTriangleMesh *triMesh, btCollisionShape *collShape, btDefaultMotionState* defaultMotion);
    void CreatePaddle(const btVector3 &position);
    void CreatePaddle2(const btVector3 &position);
    void CreateBumper(const btVector3 &position);
    void CreateGlass();

    void GetView();


    friend class Graphics;



  private:

    // Objects
    Object *board, *board2, *topIslandObj, *backBoard, *ball, *bumper, *bumper2, *bumper3, *spring, *stick, *cubeObject, *leftPaddle, *rightPaddle, *capsule, *capsule2,
    *bigIslandObj, *leftArmObj, *leftIslandObj, *rightArmObj, *small_island_leftObj, *small_island_rightObj, *thing_1Obj, *thing_2Obj, *thing_3Obj, *thing_4Obj, *upper_islandObj;

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

    // Collision Shapes
    btCollisionShape *table, *tableBot, *topIsland, *glass, *cylinder, *sphere, *left, *right, *cube, *capsuleShape, *capsuleShape2,
        *bigIsland, *leftArm, *leftIsland, *rightArm, *small_island_left, *small_island_right, *thing_1, *thing_2, *thing_3, *thing_4, *upper_island;


    btCollisionShape *btBumper, *btBumper2, *btBumper3, *btSpring, *btStick;

    btTriangleMesh *objTriMesh[25];

    std::vector<btRigidBody*> rigidBody;
};

#endif
