#include "object.h"
#include <fstream>
#include <cstring>

Object::Object()
{
  // Initialize
  myScene = NULL;
  angle = 0;

}

Object::~Object()
{
  Geometry.clear();
  Indices.clear();
}

void Object::CreateObject(std::string objFile, std::string textureFile, btTriangleMesh *triMesh)
{


  // Open File Data
  if(!Initialize(objFile))
  {
    std::cerr<< "OBJ file was not found, ending program.\n";
    exit(1);
  }

  SetVertices(triMesh);


  getTextures(textureFile);


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

  // check if file exits
  if(myScene == NULL)
  {
    return false;
  }
return true;
}

void Object::SetVertices(btTriangleMesh *triMesh)
{
  // Declare variables
    // myScene currently holds all .obj data
    // grab the number of meshes
  int index = 0;
  Vertex temp;

  btVector3 triArray[3];

  // Iterate through Meshes
  for(unsigned int iMesh = 0; iMesh < myScene->mNumMeshes; iMesh++) // mesh index iterator
  {
    aiMesh* model = myScene->mMeshes[iMesh];

    // Iterate through faces
    for(int iFaces = 0; iFaces < model->mNumFaces; iFaces++) // face index
    {
      // for each indice in the mesh
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

        // check for normal vectorss
        if(model->mNormals != NULL)
        {
          temp.normal[0] = model->mNormals[index].x;
          temp.normal[1] = model->mNormals[index].y;
          temp.normal[2] = model->mNormals[index].z;
        }

        // Load Vertex Position
        for(int j = 0; j < 3; j++)  // iterate through each face
        {
          // Index info corresponds to a vertex position
          temp.position[j] = model->mVertices[index][j];
        }

        triArray[i] = btVector3( position.x, position.y, position.z);

        // Push back Index and Geomtry info
        Indices.push_back(index);
        Geometry.push_back(temp);
      }
      if(triMesh != NULL)
      {
        triMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
      }
    }
  }

}

void Object::Update(btRigidBody* rigidBodyID)
{
  // Initialize Physics
  btTransform trans;
  btScalar m[16];


  // Move Objects
  rigidBodyID->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  model = glm::make_mat4(m);

}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::getTextures(std::string textureFile)
{
  InitializeMagick(textureFile.c_str());
  Image myImage;

  myImage.read(textureFile);

  int imageWidth = myImage.columns();
  int imageHeight = myImage.rows();
  // Not too sure what this stuff is..
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