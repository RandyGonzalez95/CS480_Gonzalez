#include "object.h"
#include <fstream>
#include <cstring>


Object::Object(char * objFile)
{
  // Initialize
  myScene = NULL;

  // Open File Data
  if(!Initialize(objFile))
  {
    std::cerr<< "OBJ file was not found, ending program";
    exit(1);
  }



  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Geometry.size(), &Geometry[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Geometry.clear();
  Indices.clear();
}

bool Object::Initialize(char *objFile)
{
  // Open File
  myScene = importer.ReadFile(objFile, aiProcess_Triangulate);

  // check if file exits
  if(myScene == NULL)
  {
    return false;
  }
return true;
}

void Object::SetVertices()
{
  // Declare variables
  int meshes = 0;
  // myScene currently holds all .obj data
  // grab the number of meshes
  meshes = myScene->mNumMeshes; // usually just one
  // Iterate through mMeshes
  for(meshes = 0; meshes < myScene->mNumMeshes; meshes++)
  {


  }

  // find number of faces within the mMeshes
    // iterate through each face

    // Grab index info of the faces

    // Index info corresponds to a vertex position


}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
