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

  SetVertices();


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
    // myScene currently holds all .obj data
    // grab the number of meshes
  int meshes = myScene->mNumMeshes;// usually just one
  int faces = 0;
  int index = 0;
  Vertex temp;

  // Iterate through mMeshes
  for(int iMesh = 0; iMesh < meshes; iMesh++) // mesh index iterator
  {
    // Find number of faces per mesh
    faces = myScene->mMeshes[iMesh]->mNumFaces;
    for(int iFaces = 0; iFaces <faces; iFaces++) // face index
    {
      // for each face in the mesh
      for(int i = 0; i<3; i++)
      {
          // Grab index info of the faces
        index = myScene->mMeshes[iMesh]->mFaces[iFaces].mIndices[i];
        for(int j =0; j<3; j++)  // iterate through each face
        {
          // Index info corresponds to a vertex position
          temp.position[j] = myScene->mMeshes[iMesh]->mVertices[index][j];
          temp.color[j] = 1.0f;
        }

        // Push back Index and Geomtry info
        Indices.push_back(index);
        Geometry.push_back(temp);
      }
    }
  }

}

glm::mat4 Object::GetModel()
{
  //model = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(1.0,0.0,0.0));
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
