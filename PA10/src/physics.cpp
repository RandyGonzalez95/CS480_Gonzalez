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
  leftPaddle = new Object();
  rightPaddle = new Object();

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
  delete glass;
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
  bumper->CreateObject("../models/bumper.obj", "../models/bumper.jpeg", NULL);
  cubeObject->CreateObject("../models/cube.obj", "../models/brick.jpeg", NULL);
  ball->CreateObject("../models/sphere.obj", "../models/steel.jpg", NULL);
  leftPaddle->CreateObject("../models/leftPaddle2.obj", "../models/steel.jpg", objTriMesh[1]);
  rightPaddle->CreateObject("../models/rightPaddle2.obj", "../models/steel.jpg", objTriMesh[2]);

  // Table
  table = new btBvhTriangleMeshShape(objTriMesh[0], true);

  // Cylinder
  cylinder = new btCylinderShape(btVector3(1.0,1.0,1.0));

  // sphere
  sphere = new btSphereShape(0.5);

  // cube
  cube = new btBoxShape(btVector3(1.0,1.0,1.0));

  // paddles
  left = new btBvhTriangleMeshShape(objTriMesh[1], true);
  right = new btBvhTriangleMeshShape(objTriMesh[2], true);

  glass = new btStaticPlaneShape(btVector3(0.0, -1.0, 0.0), 0);

  // Create Motion state
  btDefaultMotionState *tableMS = NULL;
  tableMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *cylinderMS = NULL;
  cylinderMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(3,1,9)));

  btDefaultMotionState *sphereMS = NULL;
  sphereMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-9, 0,-12)));

  btDefaultMotionState *cubeMS = NULL;
  cubeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *glassMS = NULL;
  glassMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 2.5, 0)));

  btDefaultMotionState *leftMS = NULL;
  leftMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *rightMS = NULL;
  rightMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  // set mass
  btScalar mass(100);
  // inertia
  btVector3 inertia(1,1,1);

  // Set inertia for each shape
  cylinder->calculateLocalInertia(mass,inertia);
  sphere->calculateLocalInertia(mass,inertia);
  cube->calculateLocalInertia(mass,inertia);
  table->calculateLocalInertia(mass,inertia);
  left->calculateLocalInertia(mass,inertia);
  right->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMS, table, inertia);
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMS, cylinder, inertia);
  btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMS, sphere, inertia);
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass, cubeMS, cube, inertia);
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, glassMS, glass, inertia);

  btRigidBody::btRigidBodyConstructionInfo leftRigidBodyCI(0, leftMS, left, inertia);
  btRigidBody::btRigidBodyConstructionInfo rightRigidBodyCI(0, rightMS, right, inertia);

  // Add RigidBody
  btRigidBody *temp = new btRigidBody(tableRigidBodyCI); // table
  rigidBody.push_back(temp);

  temp = new btRigidBody(cylinderRigidBodyCI); // bumper
  rigidBody.push_back(temp);

  temp = new btRigidBody(sphereRigidBodyCI); // ball
  rigidBody.push_back(temp);

  temp = new btRigidBody(cubeRigidBodyCI); // cube
  rigidBody.push_back(temp);

  temp = new btRigidBody(planeRigidBodyCI); // glass
  rigidBody.push_back(temp);

  temp = new btRigidBody(leftRigidBodyCI); // left
  rigidBody.push_back(temp);

  temp = new btRigidBody(rightRigidBodyCI); // right
  rigidBody.push_back(temp);


  // Add to World
  dynamicsWorld->addRigidBody(rigidBody[0]); // table
  dynamicsWorld->addRigidBody(rigidBody[1]); // bumper
  dynamicsWorld->addRigidBody(rigidBody[2]); // ball
  dynamicsWorld->addRigidBody(rigidBody[3]); // cube
  dynamicsWorld->addRigidBody(rigidBody[4]); // ground
  dynamicsWorld->addRigidBody(rigidBody[5]); // leftPaddle
  dynamicsWorld->addRigidBody(rigidBody[6]); // rightPaddle

}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int index)
{
  return rigidBody[index];
}
