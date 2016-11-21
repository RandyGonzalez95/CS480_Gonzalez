#include "physics.h"
#include <iostream>

Physics::Physics()
{
  index = 0;
  mass = btScalar(10);
  inertia = btVector3(1,1,1);

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
  bigIslandObj = new Object();
  leftArmObj = new Object();
  leftIslandObj = new Object();
  rightArmObj = new Object();
  small_island_leftObj = new Object();
  small_island_rightObj = new Object();
  thing_1Obj = new Object();
  thing_2Obj = new Object();
  thing_3Obj = new Object();
  thing_4Obj = new Object();
  upper_islandObj = new Object();
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
  dynamicsWorld->setGravity(btVector3(0, -9.81, 9.81));

  // check if the world exists
  if( dynamicsWorld == NULL)
    return false;


  return true;
}

void Physics::Pinball()
{
  // set mass
//  btScalar mass(10);
  // inertia
//  btVector3 inertia(1,1,1);
  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *tableMS = NULL;
  tableMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/table.obj", "../models/image.jpg", board, objTriMesh[triIndex], table, tableMS); // index = 0, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *bigIslandMS = NULL;
  bigIslandMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/bigIsland.obj", "../models/image.jpg", bigIslandObj, objTriMesh[triIndex], bigIsland, bigIslandMS); // index = 1, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *leftArmMS = NULL;
  leftArmMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/leftArm.obj", "../models/image.jpg", leftArmObj, objTriMesh[triIndex], leftArm, leftArmMS); // index = 2, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *leftIslandMS = NULL;
  leftIslandMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/leftIsland.obj", "../models/image.jpg", leftIslandObj, objTriMesh[triIndex], leftIsland, leftIslandMS); // index = 3, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *rightArmMS = NULL;
  rightArmMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/rightArm.obj", "../models/image.jpg", rightArmObj, objTriMesh[triIndex], rightArm, rightArmMS); // index = 4, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *small_island_leftMS = NULL;
  small_island_leftMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/small_island_left.obj", "../models/image.jpg", small_island_leftObj, objTriMesh[triIndex], small_island_left, small_island_leftMS); // index = 5, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *small_island_rightMS = NULL;
  small_island_rightMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/small_island_right.obj", "../models/image.jpg", small_island_rightObj, objTriMesh[triIndex], small_island_right, small_island_rightMS); // index = 6, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *thing1MS = NULL;
  thing1MS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/thing_1.obj", "../models/image.jpg", thing_1Obj, objTriMesh[triIndex], thing_1, thing1MS); // index = 7, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *thing2MS = NULL;
  thing2MS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/thing_2.obj", "../models/image.jpg", thing_2Obj, objTriMesh[triIndex], thing_2, thing2MS); // index = 8, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *thing3MS = NULL;
  thing3MS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/thing_3.obj", "../models/image.jpg", thing_3Obj, objTriMesh[triIndex], thing_3, thing3MS); // index = 9, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *thing4MS = NULL;
  thing4MS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/thing_4.obj", "../models/image.jpg", thing_4Obj, objTriMesh[triIndex], thing_4, thing4MS); // index = 10, table

  objTriMesh[triIndex] = new btTriangleMesh();

  btDefaultMotionState *upper_islandMS = NULL;
  upper_islandMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  CreateTableItem("../FinalModels/upper_island.obj", "../models/image.jpg", upper_islandObj, objTriMesh[triIndex], upper_island, upper_islandMS); // index = 11, table

  CreateGlass(); // index = 12; glassphysicsWorld->capsule->Scale(0.3);
  CreateSphere(); // index = 13;, ball
  CreateCube(); // index = 14; cube
  //CreateBumper(btVector3(0,0,12)); // index = 15; bumper
  CreatePaddle(btVector3(-1, 0.2, 8)); // index = 16, right paddle
  CreatePaddle2(btVector3(1.5, 0.2, 7.8)); // index = 17, left paddle



  // hinge constraint
  rigidBody[5]->setDamping( 0.05f, 0.85f );
  rigidBody[6]->setDamping( 0.05f, 0.85f );


  /*const btVector3 btPivotA(0.0f, 0.0f, 5.0f );
  btVector3 btAxisA( 0.0f, 0.0f, 1.0f );
  // set mass
  btScalar mass(10);
  // inertia
  btVector3 inertia(1,1,1);
  const btVector3 btPivotB(0.0f, 10.0f, 0.0f );
  btVector3 btAxisB( 0.0f, 1.0f, 0.0f );*/


  const btVector3 btPivotA(-0.9f, 1.0f, -0.03f ); // right next to the door slightly outside
	btVector3 btAxisA( 0.0f, 1.0f, 0.0f );  // set mass


  //const btVector3 btPivotA( 0.0f, 0.0f, .0f ); // right next to the door slightly outside
	//btVector3 btAxisA( 0.0f, 1.0f, 0.0f );  // set mass


	btHingeConstraint *joint = new btHingeConstraint( *rigidBody[15], btPivotA, btAxisA );

	joint->setLimit(  -SIMD_PI  / 4 , SIMD_PI * 0.2f  );


	dynamicsWorld->addConstraint(joint);


  const btVector3 btPivotB(0.15f, 1.0f, 0.05f ); // right next to the door slightly outside
  btVector3 btAxisV( 0.0f, 1.0f, 0.0f );

	btHingeConstraint *joint2 = new btHingeConstraint( *rigidBody[16], btPivotA, btAxisA );

	joint2->setLimit( -SIMD_PI / 8, SIMD_PI * 0.2f);


	 dynamicsWorld->addConstraint(joint2);


  /*btHingeConstraint *joint = new btHingeConstraint( *rigidBody[0],
   *rigidBody[5],
   btVector3( btScalar( -3.0 ), btScalar( 1.0 ), btScalar( -9.0 ) ),
   btVector3( btScalar( 0.0 ), btScalar( 0.0 ), btScalar( 0.0 ) ),
   btVector3( btScalar( 0.0 ), btScalar( 1.0 ), btScalar( 0.0 ) ),
   btVector3( btScalar( 0.0 ), btScalar( 0.0 ), btScalar( 0.0 ) ) );
table
   btHingeConstraint *joint2 = new btHingeConstraint( *rigidBody[0],
      *rigidBody[6],
      btVector3( btScalar( 3.0 ), btScalar( 1.0 ), btScalar( -9.0 ) ),
      btVector3( btScalar( 0.0 ), btScalar( 0.0 ), btScalar( 0.0 ) ),
      btVector3( btScalar( 0.0 ), btScalar( 1.0 ), btScalar( 0.0 ) ),
      btVector3( btScalar( 0.0 ), btScalar( 0.0 ), btScalar( 0.0 ) ) );*/

  //joint->setLimit( -SIMD_PI*0.8f, SIMD_PI, 0.9f, 0.01f, 0.0f);
  //joint2->setLimit( btScabtDefaultMotionState* defaulMotionlar( 30 ), btScalar( 60 ) );

  //dynamicsWorld->addConstraint( joint, true );
  //dynamicsWorld->addConstraint( joint2, true );
}

void Physics::CreateSphere()
{
  ball->CreateObject("../models/sphere.obj", "../models/steel.jpg", NULL);

  // sphere
  sphere = new btSphereShape(0.2);

  // Create Motion StateleftPaddle
  btDefaultMotionState *sphereMS = NULL;
  sphereMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(4.4, 0.2, 8.5)));

  // Set Mass and inertia
  sphere->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMS, sphere, inertia);


  btRigidBody *temp = new btRigidBody(sphereRigidBodyCI); // ball
  rigidBody.push_back(temp);

  rigidBody[index]->setActivationState(DISABLE_DEACTIVATION);

  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateCube()
{
  // cube
  cubeObject->CreateObject("../models/cube.obj", "../models/brick.jpeg", NULL);
  cube = new btBoxShape(btVector3(0.2,0.2,0.2));

  // Set Motion State
  btDefaultMotionState *cubeMS = NULL;
  cubeMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 1, 0)));

  // Create Rigid Bodys
  cube->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(mass*3, cubeMS, cube, inertia);

  // Add to World
  btRigidBody *temp = new btRigidBody(cubeRigidBodyCI); // cube
  rigidBody.push_back(temp);

  rigidBody[index]->setActivationState(DISABLE_DEACTIVATION);

  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateTable()
{

  // Table
  objTriMesh[triIndex] = new btTriangleMesh();

  board->CreateObject("../FinalModels/table.obj", "../models/image.jpg", objTriMesh[0]);

  table = new btBvhTriangleMeshShape(objTriMesh[0], true);

    // Create Motion state
  btDefaultMotionState *tableMS = NULL;
  tableMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

  // Set mass and inertia
  table->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, tableMS, table, inertia);

  // Add to World 0.2f
  btRigidBody *temp = new btRigidBody(tableRigidBodyCI); // table
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);

  index++;
  triIndex++;

}

void Physics::CreateTableItem(std::string objectFile, std::string textureFile, Object* obj, btTriangleMesh *triMesh, btCollisionShape *collShape, btDefaultMotionState* defaultMotion)
{
  obj->CreateObject(objectFile, textureFile, triMesh);

  collShape = new btBvhTriangleMeshShape(triMesh, true);

  // Set mass and inertia
  collShape->calculateLocalInertia(mass,inertia);

  // Create RigidBody
  btRigidBody::btRigidBodyConstructionInfo tableRigidBodyCI(0, defaultMotion, collShape, inertia);

  // Add to World
  btRigidBody *temp = new btRigidBody(tableRigidBodyCI); // table
  rigidBody.push_back(temp);

  dynamicsWorld->addRigidBody(rigidBody[index]);

  index++;
  triIndex++;


}

void Physics::CreatePaddle(const btVector3 &position)
{
  // Create capsule object
  capsule->CreateObject( "../models/leftPaddle.obj", "../models/steel.jpg", NULL);
  capsuleShape = new btBoxShape(btVector3(0.2,0.2,0.2));

  // Set Motion State
  btDefaultMotionState *capsuleMS = NULL;
  capsuleMS = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));

  // Set Rigid Body
  capsuleShape->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI(mass , capsuleMS, capsuleShape, inertia);

  // Add to world
  btRigidBody *temp = new btRigidBody(capsuleRigidBodyCI); // left capsule
  rigidBody.push_back(temp);

  rigidBody[index]->setActivationState(DISABLE_DEACTIVATION);


  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreatePaddle2(const btVector3 &position)
{
  // Create capsule object
  capsule2->CreateObject( "../models/rightPaddle.obj", "../models/steel.jpg", NULL);
  capsuleShape2 = new btBoxShape(btVector3(0.2,0.2,0.2));

  // Set Motion State
  btDefaultMotionState *capsuleMS2 = NULL;
  capsuleMS2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));

  // Set Rigid Body
  capsuleShape2->calculateLocalInertia(mass,inertia);
  btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI2(mass, capsuleMS2, capsuleShape2, inertia);

  // Add to world
  btRigidBody *temp = new btRigidBody(capsuleRigidBodyCI2); // left capsule
  rigidBody.push_back(temp);

  rigidBody[index]->setActivationState(DISABLE_DEACTIVATION);

  dynamicsWorld->addRigidBody(rigidBody[index]);
  index++;
}

void Physics::CreateBumper(const btVector3 &position)
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

void Physics::CreateGlass()
{
  // Place Glass object
  glass = new btStaticPlaneShape(btVector3(0.0, 0.0, 0.0), 0);
  btDefaultMotionState *glassMS = NULL;
  // Motion State
  glassMS = new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(0, 1.5, 0)));
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
