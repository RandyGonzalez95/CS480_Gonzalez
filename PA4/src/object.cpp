#include "object.h"
#include <fstream>
#include <cstring>


Object::Object(char * objFile)
{
  Geometry = new vertex[1000000];
  Indices = new unsigned int[10000000];
  // check for object file
  if( !LoadOBJ(objFile) )
  {
    std::cerr<< "ERROR: Object was not able to load. Ending program.\n";
    exit(1);
  }
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  /*Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };*/

/*  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };*/

  // The index works at a 0th index
  for(unsigned int i = 0; i < iSize; i++)
  {
    Indices[i] = Indices[i] - 1;
  }


  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vSize, &Geometry[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * iSize, &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  // clear vertices and Indices
  delete []Geometry;
  delete []Indices;

}

bool Object::LoadOBJ(char* obj)
{
  // declare file variables
  std::ifstream fin;
  char ignore; // assume not more than 300 chars in one line
  std::string dummy; //used to see where we are at the file
  float ignoreNum; // this will store useless face information

  int vertexSize = 0; // how many vertices there are on file
  int index = 0; // index of the Indices array


  // open File
  fin.clear();
  fin.open(obj);

  // check if file is good
  if(!fin.good())
    return false;
  else
  {
    while(fin.good())
    {
      fin>> dummy;
      // first ignore any unnecessary lines
        // Til we reach all the vertex information
      if(dummy=="v") // meaning we are at the vertices
        {
          for(int i = 0; i< 3; i++ )// for the three positions
            {
              fin>> Geometry[vertexSize].position[i]; // stores floats to the three positions
            }
          vertexSize++; // go to next vertex

        }
      else if(dummy=="f") // we are at the faces
        {
          for(int j= 0; j<3;j++)// loop through 3 faces (Triangulated)
            {
              fin>>Indices[index]>>ignore>>ignore>>ignoreNum;
              index++; // go to next index
            }
        }// end else if
    }// end while loop
  }// end else

  // Store sizes of vertex and index arrays
  vSize = vertexSize;
  iSize = index;

  // close the file
  fin.close();
  return true;
}

glm::mat4 Object::GetModel()
{
  model = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f));
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

  glDrawElements(GL_TRIANGLES, iSize, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
