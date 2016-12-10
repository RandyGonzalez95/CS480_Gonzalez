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

  // Cue Ball
  CreateSphere("../models/sphere.obj", "../models/cue.png", btVector3(30,0.5,0)); // cue ball index = 0;

  // All pool table balls in order
      // 1 -15
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

  // 16 - 19
  CreateTable(); // All table items

  // 20
  CreateStick();

}

void Physics::CreateSphere(std::string objFile, std::string texture, const btVector3 &position)
{
  // Create Object
  Object *tempObject = new Object();
  tempObject->CreateObject(objFile, texture, NULL);

  tempObject->mass = btScalar(100);
  tempObject->inertia = btVector3(0,0,0);

  // collision shape
  tempObject->shape = new btSphereShape(1);
  tempObject->shape->calculateLocalInertia(tempObject->mass, tempObject->inertia);

  // Motion State
  tempObject->motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,1,1), position));

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(tempObject->mass, tempObject->motionState, tempObject->shape, tempObject->inertia);
  tempObject->rigidBody = new btRigidBody(rigidBodyCI);
  tempObject->rigidBody->setRestitution(0.9);
  tempObject->rigidBody->setDamping(0,0.8);

  // Set Active
  tempObject->rigidBody->setActivationState(DISABLE_DEACTIVATION);

  // Add to world
  dynamicsWorld->addRigidBody(tempObject->rigidBody);

  objects.push_back(tempObject);
}

void Physics::CreateStick()
{
  // Create Object
  Object *tempObject = new Object();
  tempObject->CreateObject("../models/stick.obj", "../models/image.jpg", NULL);


  tempObject->mass = btScalar(100);
  tempObject->inertia = btVector3(0,0,0);

  // Collision Shape
  tempObject->shape = new btCylinderShape(btVector3(1,1,1));
  tempObject->shape->calculateLocalInertia(tempObject->mass, tempObject->inertia);

  // Motion State
  tempObject->motionState = new btDefaultMotionState(btTransform(btQuaternion(1,0,0,1), btVector3(34,1,0)));

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(tempObject->mass, tempObject->motionState, tempObject->shape, tempObject->inertia);
  tempObject->rigidBody = new btRigidBody(rigidBodyCI);

  // Set Active
  tempObject->rigidBody->setActivationState(DISABLE_DEACTIVATION);

  // Add to World
  dynamicsWorld->addRigidBody(tempObject->rigidBody);


  // Pool Stick Implementation
  btTransform fromB(btTransform::getIdentity());

  fromB.setOrigin( btVector3(5.0f,0.0f,0.0f));

  btSliderConstraint* slider =
      new btSliderConstraint(
          *tempObject->rigidBody,
          fromB,true);

  slider->setLowerLinLimit(-5.0f);
  slider->setUpperLinLimit(5.0f);

  slider->setLowerAngLimit(-5.0f);
  slider->setUpperAngLimit(5.0f);

  dynamicsWorld->addConstraint(slider);


  objects.push_back(tempObject);
}

void Physics::CreateTable()
{
  //CreateTableItem("../models/box.obj", "../models/image.jpg");
  CreateTableItem("../models/frame.obj", "../models/images.jpg"); // 16
  CreateTableItem("../models/legs.obj", "../models/steel.jpg"); // 17
  CreateTableItem("../models/table.obj", "../models/green.jpg"); // 18
  CreateTableItem("../models/ledges.obj", "../models/ledges.png"); //19
}

void Physics::CreateTableItem(std::string objFile, std::string texture)
{
  // Create Object with texture
  Object *tempObject = new Object();
  tempObject->objTriMesh = new btTriangleMesh();
  tempObject->CreateObject(objFile, texture, tempObject->objTriMesh);

  tempObject->mass = btScalar(100);
  tempObject->inertia = btVector3(0,0,0);

  // Collision Shape
  tempObject->shape = new btBvhTriangleMeshShape(tempObject->objTriMesh, true);


  tempObject->shape->calculateLocalInertia(tempObject->mass, tempObject->inertia);

  // Motion State
  tempObject->motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0, 0 ,0)));

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, tempObject->motionState, tempObject->shape, tempObject->inertia);
  tempObject->rigidBody = new btRigidBody(rigidBodyCI);

  // Add to world
  dynamicsWorld->addRigidBody(tempObject->rigidBody);

  objects.push_back(tempObject);
}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}
