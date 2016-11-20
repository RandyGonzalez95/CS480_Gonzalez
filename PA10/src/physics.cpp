#include "physics.h"
#include <iostream>

Physics::Physics()
{
  index = 0;

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
  capsule = new Object();
  capsule2 = new Object();

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
  dynamicsWorld->setGravity(btVector3(0,-9.81,-9.81));

  // check if the world exists
  if( dynamicsWorld == NULL)
    return false;


  return true;
}

void Physics::Pinball()
{

  // set mass
  btScalar mass(10);
  // inertia
  btVector3 inertia(1,1,1);


  CreateTable(0, inertia); // index = 0, table
  CreateGlass(0, inertia); // index = 1; glass
  CreateSphere(mass, inertia ); // index = 2;, ball
  CreateCube(mass, inertia ); // index = 3; cube
  CreateBumper(mass, inertia, btVector3(3,1,9)); // index = 4; bumper
  CreatePaddle(mass, inertia, btVector3(0, 1, 0)); // index = 5, right paddle
  CreatePaddle2(mass, inertia, btVector3(5, 1, 0)); // index = 6, left paddle



  // hinge constraint
  /*rigidBody[5]->setDamping( 0.05f, 0.85f );
  rigidBody[6]->setDamping( 0.05f, 0.85f );


  const btVector3 btPivotA(0.0f, 0.0f, 3.0f );
  btVector3 btAxisA( 0.0f, 0.0f, 1.0f );

  const btVector3 btPivotB(0.0f, 0.0f, 3.0f );
  btVector3 btAxisB( 0.0f, 0.0f, 1.0f );


  btHingeConstraint *joint = new btHingeConstraint( *rigidBody[5], btPivotA, btAxisA );
  btHingeConstraint *joint2 = new btHingeConstraint( *rigidBody[6], btPivotA, btAxisA );

/*btHingeConstraint *joint = new btHingeConstraint( *rigidBody[5],
   *rigidBody[6],
   btVector3( btScalar( 0.0 ), btScalar( -0.3 / 2.0 ), btScalar( 0.0 ) ),
   btVector3( btScalar( 0.0 ), btScalar( 0.3 / 2.0 ), btScalar( 0.0 ) ),
   btVector3( btScalar( 0.0 ), btScalar( 0.0 ), btScalar( 1.0 ) ),
     btVector3( btScalar( 0.0 ), btScalar( 0.0 ), btScalar( 1.0 ) ) );*/

  //joint->setLimit( btScalar( 30 ), btScalar( 60 ) );
  //joint2->setLimit( btScalar( 30 ), btScalar( 60 ) );

  //dynamicsWorld->addConstraint( joint, true );
  //dynamicsWorld->addConstraint( joint2, true );
}

void Physics::CreateSphere( btScalar mass, btVector3 inertia )
{
  ball->CreateObject("../models/sphere.obj", "../models/steel.jpg", NULL);

  // sphere
  sphere = new btSphereShape(0.5);

  // Create Motion State
  btDefaultMotionState *sphereMS = NULL;
  sphereMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-9, 0,-12)));

  // Set Mass and inertia
  sphere->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMS, sphere, inertia);


  btRigidBody *temp = new btRigidBody(sphereRigidBodyCI); // ball
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateCube( btScalar mass, btVector3 inertia )
{
  // cube
  cubeObject->CreateObject("../models/cube.obj", "../models/brick.jpeg", NULL);
  cube = new btBoxShape(btVector3(1.0,1.0,1.0));

  // Set Motion State
  btDefaultMotionState *cubeMS = NULL;
  cubeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));

  // Create Rigid Bodys
  cube->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass, cubeMS, cube, inertia);

  // Add to World
  btRigidBody *temp = new btRigidBody(cubeRigidBodyCI); // cube
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateTable(btScalar mass, btVector3 inertia)
{

  // Table
  objTriMesh[0] = new btTriangleMesh();

  board->CreateObject("../models/table2.obj", "../models/image.jpg", objTriMesh[0]);

  table = new btBvhTriangleMeshShape(objTriMesh[0], true);

    // Create Motion state
  btDefaultMotionState *tableMS = NULL;
  tableMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  // Set mass and inertia
  table->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMS, table, inertia);

  // Add to World
  btRigidBody *temp = new btRigidBody(tableRigidBodyCI); // table
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);

  index++;

}

void Physics::CreatePaddle(btScalar mass, btVector3 inertia, const btVector3 &position)
{
  // Create capsule object
  capsule->CreateObject( "../models/capsule.obj", "../models/capsule0.jpg", NULL);
  capsuleShape = new btCapsuleShape( btScalar(1), btScalar(1.0));

  // Set Motion State
  btDefaultMotionState *capsuleMS = NULL;
  capsuleMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));

  // Set Rigid Body
  capsuleShape->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI(mass, capsuleMS, capsuleShape, inertia);

  // Add to world
  btRigidBody *temp = new btRigidBody(capsuleRigidBodyCI); // left capsule
  rigidBody.push_back(temp);


  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreatePaddle2(btScalar mass, btVector3 inertia, const btVector3 &position)
{
  // Create capsule object
  capsule2->CreateObject( "../models/capsule.obj", "../models/capsule0.jpg", NULL);
  capsuleShape2 = new btCapsuleShape( btScalar(1), btScalar(1.0));

  // Set Motion State
  btDefaultMotionState *capsuleMS2 = NULL;
  capsuleMS2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));

  // Set Rigid Body
  capsuleShape2->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI2(mass, capsuleMS2, capsuleShape2, inertia);

  // Add to world
  btRigidBody *temp = new btRigidBody(capsuleRigidBodyCI2); // left capsule
  rigidBody.push_back(temp);


  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateBumper(btScalar mass, btVector3 inertia, const btVector3 &position)
{
  // Create Cylinder Object
  bumper->CreateObject("../models/bumper.obj", "../models/bumper.jpeg", NULL);
  cylinder = new btCylinderShape(btVector3(1.0,1.0,1.0));

  // Set Motion State
  btDefaultMotionState *cylinderMS = NULL;
  cylinderMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), position));

  // Add Rigid Body
  cylinder->calculateLocalInertia(mass,inertia);

  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMS, cylinder, inertia);
  btRigidBody *temp = new btRigidBody(cylinderRigidBodyCI); // bumper
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateGlass(btScalar mass, btVector3 inertia)
{
  // Place Glass object
  glass = new btStaticPlaneShape(btVector3(0.0, -1.0, 0.0), 0);
  btDefaultMotionState *glassMS = NULL;
  // Motion State
  glassMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 2.5, 0)));
  // rigidBody
  btRigidBody::btRigidBodyConstructionInfo planeRigidBodyCI(0, glassMS, glass, inertia);

  // Add to world
  btRigidBody *temp = new btRigidBody(planeRigidBodyCI); // glass
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);

  index++;
}

btDiscreteDynamicsWorld* Physics::getWorld()
{
  return dynamicsWorld;
}

btRigidBody* Physics::getRigidBody(int index)
{
  return rigidBody[index];
}
