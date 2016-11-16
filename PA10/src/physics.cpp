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

  // Initialize Models
  board = new Object();
  bumper = new Object();
  ball = new Object();
  cubeObject = new Object();

  Pinball();

}

Physics::~Physics()
{
  // delete all pointers
  delete broadphase;
  delete collisionConfiguration;
  delete dispatcher;
  delete solver;
  delete table;
  delete ground;
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

  /*rightWall = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), -4);
  leftWall = new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), -6);
  topWall = new btStaticPlaneShape(btVector3(1.0, 0.0, 0.0), -17.5);
  bottomWall = new btStaticPlaneShape(btVector3(0.0, 0.0, 1.0), -8.5);*/

  // Object tri meshes
  objTriMesh[0] = new btTriangleMesh();
  objTriMesh[1] = new btTriangleMesh();
  objTriMesh[2] = new btTriangleMesh();

  board->CreateObject("../models/table2.obj", "../models/image.jpg", objTriMesh[0]);
  bumper->CreateObject("../models/bumper.obj", "../models/water.jpg", NULL);
  cubeObject->CreateObject("../models/cube.obj", "../models/brick.jpeg", NULL);
  ball->CreateObject("../models/sphere.obj", "../models/steel.jpg", NULL);

  // Table
  table = new btBvhTriangleMeshShape(objTriMesh[0], true);

  // Cylinder
  cylinder = new btCylinderShape(btVector3(1.0,1.0,1.0));

  // sphere
  sphere = new btSphereShape(0.5);

  // cube
  cube = new btBoxShape(btVector3(1.0,1.0,1.0));

  glass = new btStaticPlaneShape(btVector3(0.0, -1.0, 0.0), 0);

  // Create Motion state
  btDefaultMotionState *tableMS = NULL;
  tableMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  /*btDefaultMotionState *rightWallMS= NULL;
  rightWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, -1, 1), btVector3(-2, 0, 0)));

  btDefaultMotionState *leftWallMS= NULL;
  leftWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 1, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *topWallMS = NULL;
  topWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *bottomWallMS = NULL;
  bottomWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 1, 1), btVector3(0, 0, 0)));*/

  btDefaultMotionState *cylinderMS = NULL;
  cylinderMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(3,1,9)));

  btDefaultMotionState *sphereMS = NULL;
  sphereMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 0,-8)));

  btDefaultMotionState *cubeMS = NULL;
  cubeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *glassMS = NULL;
  glassMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 2.5, 0)));

  // set mass
  btScalar mass(100);
  // inertia
  btVector3 inertia(1,1,1);

  // Set inertia for each shape
  cylinder->calculateLocalInertia(mass,inertia);
  sphere->calculateLocalInertia(mass,inertia);
  cube->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMS, table, inertia);
  /*btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI2(0, rightWallMS, rightWall, inertia);
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI3(0, leftWallMS, leftWall, inertia);
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI4(0, topWallMS, topWall, inertia);
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI5(0, bottomWallMS, bottomWall, inertia);*/
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMS, cylinder, inertia);
  btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMS, sphere, inertia);
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass, cubeMS, cube, inertia);
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, glassMS, glass, inertia);

  // Add RigidBody
  //btRigidBody *temp = new btRigidBody(planeRigidBodyCI);
  //rigidBody.push_back(temp);

  btRigidBody *temp = new btRigidBody(tableRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(cylinderRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(sphereRigidBodyCI);
  rigidBody.push_back(temp);

  //temp = new btRigidBody(planeRigidBodyCI2);
  //rigidBody.push_back(temp);

  //temp = new btRigidBody(planeRigidBodyCI3);
  //rigidBody.push_back(temp);

  temp = new btRigidBody(cubeRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(planeRigidBodyCI);
  rigidBody.push_back(temp);
  //temp = new btRigidBody(planeRigidBodyCI4);
  //rigidBody.push_back(temp);

  //temp = new btRigidBody(planeRigidBodyCI5);
  //rigidBody.push_back(temp);

//  rigidBody[0]->activate(true);
  //rigidBody[0]->applyForce(btVector3(0,0,0), btVector3(dt,code, 0,0,0));
  // Add to world
  dynamicsWorld->addRigidBody(rigidBody[0]); // table
  dynamicsWorld->addRigidBody(rigidBody[1]); // bumper
  dynamicsWorld->addRigidBody(rigidBody[2]); // ball
  dynamicsWorld->addRigidBody(rigidBody[3]); // cube
  dynamicsWorld->addRigidBody(rigidBody[4]); // ground
  //dynamicsWorld->addRigidBody(rigidBody[4]); // left wall
  //dynamicsWorld->addRigidBody(rigidBody[5]); // cube
  //dynamicsWorld->addRigidBody(rigidBody[6]); // top wall
  //dynamicsWorld->addRigidBody(rigidBody[7]); // bot wall
}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int index)
{
  return rigidBody[index];
}
