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
  ball = new Object();
  bumper1 = new Object();
  bumper2 = new Object();
  bumper3 = new Object();
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
  delete board;
  delete ball;
  delete bumper1;
  delete bumper2;
  delete bumper3;
  delete leftPaddle;
  delete rightPaddle;
  delete objTriMesh[0];
  delete objTriMesh[1];
  delete objTriMesh[2];
  delete objTriMesh[3];
  delete objTriMesh[4];
  delete objTriMesh[5];
  delete objTriMesh[6];
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

  // Object tri meshes
  objTriMesh[0] = new btTriangleMesh();
  objTriMesh[1] = new btTriangleMesh();
  objTriMesh[2] = new btTriangleMesh();
  objTriMesh[3] = new btTriangleMesh();
  objTriMesh[4] = new btTriangleMesh();
  objTriMesh[5] = new btTriangleMesh();
  objTriMesh[6] = new btTriangleMesh();

  board->CreateObject("../models/UsableModels/table.obj", "../models/image.jpg", objTriMesh[0]);
  table = new btBvhTriangleMeshShape(objTriMesh[0], true);

  leftPaddle->CreateObject("../models/UsableModels/leftPaddle.obj", "../models/water.jpg", objTriMesh[1]);
  paddleLeft = new btBvhTriangleMeshShape(objTriMesh[1], true);

  rightPaddle->CreateObject("../models/UsableModels/rightPaddle.obj", "../models/water.jpg", objTriMesh[2]);
  paddleRight = new btBvhTriangleMeshShape(objTriMesh[2], true);

  ball->CreateObject("../models/UsableModels/pinball.obj", "../models/steel.jpg", objTriMesh[3]);
  tableBall = new btBvhTriangleMeshShape(objTriMesh[3], true);

  bumper1->CreateObject("../models/UsableModels/bumper1.obj", "../models/steel.jpg", objTriMesh[4]);
  bumperOne = new btBvhTriangleMeshShape(objTriMesh[4], true);

  bumper2->CreateObject("../models/UsableModels/bumper2.obj", "../models/steel.jpg", objTriMesh[5]);
  bumperTwo = new btBvhTriangleMeshShape(objTriMesh[5], true);

  bumper3->CreateObject("../models/UsableModels/bumper3.obj", "../models/steel.jpg", objTriMesh[6]);
  bumperThree = new btBvhTriangleMeshShape(objTriMesh[6], true);


  // Create Motion state
  btDefaultMotionState *tableMS = NULL;
  tableMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

//  btDefaultMotionState *groundMS = NULL;
//  groundMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 0, 0)));

  /*btDefaultMotionState *rightWallMS= NULL;
  rightWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, -1, 1), btVector3(-2, 0, 0)));

  btDefaultMotionState *leftWallMS= NULL;
  leftWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 1, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *topWallMS = NULL;
  topWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 0, 0)));

  btDefaultMotionState *bottomWallMS = NULL;
  bottomWallMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 1, 1), btVector3(0, 0, 0)));*/

//  btDefaultMotionState *cylinderMS = NULL;
  //cylinderMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(3,0,9)));

//  btDefaultMotionState *sphereMS = NULL;
//  sphereMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5,0,-8)));

//  btDefaultMotionState *cubeMS = NULL;
//  cubeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  // set mass
  btScalar mass(100);
  // inertia
  btVector3 inertia(1,1,1);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMS, table, inertia);
  btRigidBody::btRigidBodyConstructionInfo paddleLeftRigidBodyCI(0, tableMS, paddleLeft, inertia);
  btRigidBody::btRigidBodyConstructionInfo paddleRightRigidBodyCI(0, tableMS, paddleRight, inertia);
  btRigidBody::btRigidBodyConstructionInfo tableBallRigidBodyCI(0, tableMS, tableBall, inertia);
  btRigidBody::btRigidBodyConstructionInfo bumperOneRigidBodyCI(0, tableMS, bumperOne, inertia);
  btRigidBody::btRigidBodyConstructionInfo bumperTwoRigidBodyCI(0, tableMS, bumperTwo, inertia);
  btRigidBody::btRigidBodyConstructionInfo bumperThreeRigidBodyCI(0, tableMS, bumperThree, inertia);

  btRigidBody *temp = new btRigidBody(tableRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(paddleLeftRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(paddleRightRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(tableBallRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(bumperOneRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(bumperTwoRigidBodyCI);
  rigidBody.push_back(temp);

  temp = new btRigidBody(bumperThreeRigidBodyCI);
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[0]); // table
  dynamicsWorld->addRigidBody(rigidBody[1]); // bumper
  dynamicsWorld->addRigidBody(rigidBody[2]); // ball
  dynamicsWorld->addRigidBody(rigidBody[3]); // cube
  dynamicsWorld->addRigidBody(rigidBody[4]); // ground
  dynamicsWorld->addRigidBody(rigidBody[5]); // cube
  dynamicsWorld->addRigidBody(rigidBody[6]); // top wall

}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int index)
{
  return rigidBody[index];
}
