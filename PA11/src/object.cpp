#include "object.h"
#include <fstream>
#include <cstring>

Object::Object()
{
  myScene = NULL;
}

Object::~Object()
{
  Geometry.clear();
  Indices.clear();

  delete shape;
  shape = NULL;
  delete motionState;
  motionState = NULL;
  delete objTriMesh;
  objTriMesh = NULL;

  delete myScene;
  myScene = NULL;
}

void Object::CreateObject(std::string objFile, std::string textureFile, btTriangleMesh *triMesh)
{
  // Open File Data
  if(!Initialize(objFile))
  {
    std::cerr<< "OBJ file was not found, ending program.\n";
    exit(1);
  }

  // Set Vertices
  SetVertices(triMesh);

  // Set Texture
  SetTexture(textureFile);

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Geometry.size(), &Geometry[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

bool Object::Initialize(std::string objFile)
{
  // Open File
  myScene = importer.ReadFile(objFile.c_str(), aiProcess_Triangulate);

  // If file doesnt exist return false
  if(myScene == NULL)
  {
    return false;
  }

  return true;
}

void Object::SetVertices(btTriangleMesh *triMesh)
{
  // Variables
  int index = 0;
  Vertex temp;
  btVector3 triArray[3];

  // Iterate through Meshes
  for(unsigned int iMesh = 0; iMesh < myScene->mNumMeshes; iMesh++)
  {
    aiMesh* model = myScene->mMeshes[iMesh];

    // Iterate through faces
    for(int iFaces = 0; iFaces < model->mNumFaces; iFaces++)
    {
      // For each indice on the face
      for(int i = 0; i < 3; i++)
      {
        aiVector3D position = model->mVertices[model->mFaces[iFaces].mIndices[i]];

        // Grab index info of the faces
        index = model->mFaces[iFaces].mIndices[i];

        // check for texture coodinates
        if(model->HasTextureCoords(0))
        {
          temp.uv[0] = model->mTextureCoords[0][index].x;
          temp.uv[1] = 1-model->mTextureCoords[0][index].y;
        }

        // check for normals
        if(model->mNormals != NULL)
        {
          temp.normal[0] = model->mNormals[index].x;
          temp.normal[1] = model->mNormals[index].y;
          temp.normal[2] = model->mNormals[index].z;
        }

        // Load Vertex Position
        for(int j = 0; j < 3; j++)  // iterate through each indice
        {
          // Index info corresponds to a vertex position
          temp.position[j] = model->mVertices[index][j];
        }

        // Set the tri Array position
        triArray[i] = btVector3( position.x, position.y, position.z);

        // Push back Index and Geomtry info
        Indices.push_back(index);
        Geometry.push_back(temp);
      }

      // Add the tri mesh to the list
      if(triMesh != NULL)
      {
        triMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
      }
    }
  }
}

void Object::Update()
{
  // Initialize Physics
  btTransform trans;
  btScalar m[16];

  // Move Objects
  rigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  model = glm::make_mat4(m);
}

void Object::SetLocation(float y, Object *cueBall)
{
  // Variables
  btTransform cueTrans;
  btVector3 cuePos;

  // Get world transform of cue ball
  cueBall->rigidBody->getMotionState()->getWorldTransform(cueTrans);
  cuePos = cueTrans.getOrigin();

  // Delete the cue ball
  delete cueBall->motionState;

  // Reset the cue ball's motion state so it is standing up right
  cueBall->motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,1,1), btVector3(cuePos.getX(), 0.5, cuePos.getZ())));
  cueBall->rigidBody->setMotionState(cueBall->motionState);
  glm::mat4 cueModel = cueBall->GetModel();

  // Fix the pool stick to the ball and the rotation that the user specifies
  model = cueModel;
  model *= glm::rotate(glm::mat4(1.0f), -1.57f, glm::vec3(0, 0, 1));
  model *= glm::rotate(glm::mat4(1.0f), y, glm::vec3(0, 1, 0));
  model *= glm::rotate(glm::mat4(1.0f), 0.2f, glm::vec3(0, 0, 1));
  model *= glm::translate(glm::mat4(1.0f), glm::vec3(2, 0, 0));
  model *= glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.5, 0));
}

void Object::unrenderPoolStick()
{
  model = glm::mat4(0.0f);
}

void Object::ResetCue()
{
  // Delete cue's motion state
  delete motionState;

  // Reset the motion state to its default
  motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,1,1), btVector3(30.0f, 0.5, 0.0f)));
  rigidBody->setMotionState(motionState);
}

glm::mat4 Object::GetModel()
{
  return model;
}

btRigidBody* Object::getRigidBody()
{
  return rigidBody;
}

btTransform Object::getTrans()
{
	btTransform trans;
	rigidBody->getMotionState()->getWorldTransform(trans);
	return trans;
}

void Object::SetTexture(std::string textureFile)
{
  InitializeMagick(textureFile.c_str());
  Image myImage;

  myImage.read(textureFile);

  int imageWidth = myImage.columns();
  int imageHeight = myImage.rows();

  Blob blob;
  myImage.magick("RGBA");
  myImage.write( &blob );

  glGenTextures(1, &Textures);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Textures);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Object::Render()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Textures);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}
