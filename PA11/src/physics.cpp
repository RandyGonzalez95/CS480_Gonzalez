#include "physics.h"
#include <iostream>

Physics::Physics()
{
  index = 0;
  numItems = 0;
  mass = btScalar(10);
  inertia = btVector3(1,1,1);
  triIndex = 0;

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



  Pool();

}

Physics::~Physics()
{
  // delete all pointers
  delete broadphase;
  delete collisionConfiguration;
  delete dispatcher;
  delete solver;
  objects.clear();
  shapes.clear();
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
  dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

  // check if the world exists
  if( dynamicsWorld == NULL)
    return false;


  return true;
}

void Physics::Pool()
{

  CreateSphere("../models/sphere.obj", "../models/cue.png", btVector3(30,0.5,0)); // cue ball index = 0;


  CreateSphere("../models/sphere.obj", "../models/ball1.jpeg", btVector3(-25,0.5,0)); // ball 1, index 1
  CreateSphere("../models/sphere.obj", "../models/ball2.jpeg", btVector3(-33,0.5,2));
  CreateSphere("../models/sphere.obj", "../models/ball3.jpeg", btVector3(-27,0.5,-1.1));
  CreateSphere("../models/sphere.obj", "../models/ball4.jpeg", btVector3(-31,0.5,-1.1));
  CreateSphere("../models/sphere.obj", "../models/ball5.jpeg", btVector3(-33,0.5,-2));
  CreateSphere("../models/sphere.obj", "../models/ball6.jpeg", btVector3(-29,0.5,2));
  CreateSphere("../models/sphere.obj", "../models/ball7.jpeg", btVector3(-33,0.5,4));
  CreateSphere("../models/sphere.obj", "../models/ball8.png", btVector3(-29,0.5,0));
  CreateSphere("../models/sphere.obj", "../models/ball9.jpeg", btVector3(-31,0.5,-3.1));
  CreateSphere("../models/sphere.obj", "../models/ball10.png", btVector3(-33,0.5,0));
  CreateSphere("../models/sphere.obj", "../models/ball11.png", btVector3(-27,0.5,1.1));
  CreateSphere("../models/sphere.obj", "../models/ball12.png", btVector3(-33,0.5,-4));
  CreateSphere("../models/sphere.obj", "../models/ball13.png", btVector3(-31,0.5,3.1));
  CreateSphere("../models/sphere.obj", "../models/ball14.png", btVector3(-29,0.5,-2));
  CreateSphere("../models/sphere.obj", "../models/ball15.png", btVector3(-31,0.5,1.1));
  
  CreateTable(); // All table items
}

void Physics::CreateSphere(std::string objFile, std::string texture, const btVector3 &position)
{
  // Create Object
  Object *temp = new Object();
  temp->CreateObject(objFile, texture, NULL);
  objects.push_back(temp);

  // collision shape
  btCollisionShape *btTemp;
  btTemp = new btSphereShape(1);
  btTemp->calculateLocalInertia(mass, inertia);
  shapes.push_back(btTemp);

  // Motion State
  btDefaultMotionState *tempMS;
  tempMS = new btDefaultMotionState(btTransform(btQuaternion(0,0,1,1), position));
  shapeMS.push_back(tempMS);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, shapeMS[index], shapes[index], inertia);
  btRigidBody *rbTemp = new btRigidBody(sphereRigidBodyCI);
  rigidBody.push_back(rbTemp);

  // Set Active
  rigidBody[index]->setActivationState(DISABLE_DEACTIVATION);


  // Add to world
  dynamicsWorld->addRigidBody(rigidBody[index]);

  // update indeces
  index++;
  numItems++;

}

void Physics::CreateCube()
{

}

void Physics::CreateTable()
{
  //CreateTableItem("../models/box.obj", "../models/image.jpg");
  CreateTableItem("../models/frame.obj", "../models/images.jpg");
  CreateTableItem("../models/legs.obj", "../models/steel.jpg");
  CreateTableItem("../models/table.obj", "../models/green.jpg");
  CreateTableItem("../models/ledges.obj", "../models/ledges.png");
}

void Physics::CreateTableItem(std::string objFile, std::string texture)
{
  // Create Object with texture
  Object *temp = new Object();
  objTriMesh[triIndex] = new btTriangleMesh();
  temp->CreateObject(objFile, texture, objTriMesh[triIndex]);
  objects.push_back(temp);

  // Collision Shape
  btCollisionShape *btTemp;
  btTemp = new btBvhTriangleMeshShape(objTriMesh[triIndex], true);


  btTemp->calculateLocalInertia(mass, inertia);
  shapes.push_back(btTemp);

  // Motion State
  btDefaultMotionState *tempMS;
  tempMS = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0, 0 ,0)));
  shapeMS.push_back(tempMS);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableItemsRigidBodyCI(0, shapeMS[index], shapes[index], inertia);
  btRigidBody *rbTemp = new btRigidBody(tableItemsRigidBodyCI);
  rigidBody.push_back(rbTemp);

  // Set Active
  //rigidBody[index]->setActivationState(DISABLE_DEACTIVATION);

  // Add to world
  dynamicsWorld->addRigidBody(rigidBody[index]);

  // update indeces
  triIndex++;
  index++;
  numItems++;
}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int i)
{
  return rigidBody[i];
}

int Physics::GetNumItems()
{
  return numItems;
}
