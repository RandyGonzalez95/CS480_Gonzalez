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
  plane = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), -1);
  plane2 = new btStaticPlaneShape(btVector3(1.0, 0.0, 0.0), -10);
  // /plane->setLocalScaling(btVector3(5,5,5));

  // Object tri meshes
  objTriMesh[0] = new btTriangleMesh();
  objTriMesh[1] = new btTriangleMesh();
  objTriMesh[2] = new btTriangleMesh();

  // Cylinder
  cylinder = new btCylinderShape(btVector3(1.0,1.0,1.0));

  // sphere
  sphere = new btSphereShape(1);

  // cube
  cube = new btBoxShape(btVector3(1.0,1.0,1.0));

  // Create Motion state
  btDefaultMotionState *planeMS = NULL;
  planeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *planeMS2= NULL;
  planeMS2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *cylinderMS = NULL;
  cylinderMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0,0,0)));

  btDefaultMotionState *sphereMS = NULL;
  sphereMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-1.6,8,0)));

  btDefaultMotionState *cubeMS = NULL;
  cubeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  // set mass
  btScalar mass(100);
  // inertia
  btVector3 inertia(1,1,1);

  // Set inertia for each shape
  plane->calculateLocalInertia(mass,inertia);
  cylinder->calculateLocalInertia(mass,inertia);
  sphere->calculateLocalInertia(mass,inertia);
  cube->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, planeMS, plane, inertia);
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI2(0, planeMS2, plane2, inertia);
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(mass, cylinderMS, cylinder, inertia);
  btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass*10, sphereMS, sphere, inertia);
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass, cubeMS, cube, inertia);

  // Add RigidBody
  btRigidBody *temp = new btRigidBody(planeRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(cylinderRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(sphereRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(planeRigidBodyCI2);
  rigidBody.push_back(temp);

  temp = new btRigidBody(cubeRigidBodyCI);
  rigidBody.push_back(temp);

//  rigidBody[0]->activate(true);
  //rigidBody[0]->applyForce(btVector3(0,0,0), btVector3(0,0,0));
  // Add to world
  dynamicsWorld->addRigidBody(rigidBody[0]);
  dynamicsWorld->addRigidBody(rigidBody[1]);
  dynamicsWorld->addRigidBody(rigidBody[2]);
  dynamicsWorld->addRigidBody(rigidBody[3]);
  dynamicsWorld->addRigidBody(rigidBody[4]);
}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int index)
{
  return rigidBody[index];
}
