#include "physics.h"
#include <iostream>

Physics::Physics()
{
  if(!Initialize())
  {
    std::cerr<<"Physics Engine failed to initialize. Ending.\n";
    exit(1);
  }

  if(!CreateWorld())
  {
    std::cerr<<"Dynamic World failed to create. Ending.\n";
    exit(1);
  }

  Pinball();

}

Physics::~Physics()
{
  // delete all pointers
  delete broadphase;
  delete collisionConfiguration;
  delete dispatcher;
  delete solver;
  delete plane;
  delete cylinder;
  delete sphere;
  delete objTriMesh[0];
  delete objTriMesh[1];
  delete objTriMesh[2];
  rigidBody.clear();
  //delete dynamicsWorld;


  // set to NULL
  broadphase = NULL;
  collisionConfiguration = NULL;
  dispatcher = NULL;
  solver = NULL;
  dynamicsWorld = NULL;


}

bool Physics::Initialize()
{
  // Allocate memory for each
  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  solver = new btSequentialImpulseConstraintSolver;


  // check if any are NULL
  if( (broadphase == NULL) || (collisionConfiguration == NULL)
      || (dispatcher==NULL) || (solver==NULL) )
  {
    return false;
  }

  return true;
}

bool Physics::CreateWorld()
{
  // Initialize the physics world
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

  // Set Gravity
  dynamicsWorld->setGravity(btVector3(0,-9.81,0));

  // check if the world exists
  if( dynamicsWorld == NULL)
    return false;


  return true;
}

void Physics::Pinball()
{
  // Plane
  plane = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 0);

  // Object tri meshes
  objTriMesh[0] = new btTriangleMesh();
  objTriMesh[1] = new btTriangleMesh();
  objTriMesh[2] = new btTriangleMesh();

  // Cylinder
  cylinder = new btCylinderShape(btVector3(1.0,1.0,1.0));

  // sphere
  sphere = new btSphereShape(2);

  // Create Motion state
  btDefaultMotionState *planeMS = NULL;
  planeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  // set mass
  btScalar mass(50);
  // inertia
  btVector3 inertia(1,2,1);

  // Set inertia for each shape
  plane->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(mass, planeMS, plane, inertia);

  // Add RigidBody
  btRigidBody *temp = new btRigidBody(planeRigidBodyCI);
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[0]);

}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int index)
{
  return rigidBody[index];
}
