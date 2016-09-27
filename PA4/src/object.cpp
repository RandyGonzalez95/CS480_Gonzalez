#include "object.h"
#include <fstream>
#include <cstring>


Object::Object(char * objFile)
{
  Geometry = new vertex[1000000];
  Indices = new unsigned int[10000000];

 RGB[0] = 1.0;
 RGB[1] = 1.0;
 RGB[2] = 1.0;



  // check for object file
  if( !LoadOBJ(objFile) )
  {
    std::cerr<< "ERROR: Object was not able to load. Ending program.\n";
    exit(1);
  }

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

bool Object::LoadMTL(std::string file, std::string colorInfo)
{
  // Declare Variables
  std::ifstream fin;
  std::string dummy, material;
  float colorValue;

  //open file
  fin.clear();
  fin.open( file.c_str() ); // since file is a string, converto to cstyle

  if(!fin.good())
  {
    return false; // file not found
  }
  else
  {
    while(fin.good())
    {
      // check for colorInfo
      fin>>dummy;
      if(dummy=="newmtl")// we are at the correct colorInfo
      {
        fin>> material;

        if(material == colorInfo) // compare the two to see if they match
        {
          fin>>dummy; // keep extracting // this should be the Ns line
          while(dummy!= "Kd")// we want to keep looping til we find Kd information
          {
            fin>>dummy;
          }// loop ends when we get to Kd information

          // These next three numbers are our RGB colors
          std::cerr<< "The colors are : ";
          for(int i=0; i<3; i++) // loop through the three colors
          {
            fin>>colorValue;
            RGB[i] = colorValue; // extract colors
            std::cerr<<RGB[i]<<" ";
          }
          std::cerr<<"\n";
          break; // break out of loop since we are done with file

        }// end if
      }// end if
    }// end while
  }// end else

  fin.close();

    // we are done
  return true;
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
  std::string mtlFile; // material file
  std::string colorInfo; // the name of the color for material
  int colorIndex = 0;


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

      // Check for Material file
      if(dummy == "mtllib")
      {
        fin>>mtlFile; // extract file name as string
        mtlFile = "../Material/" + mtlFile; // merge the FILENAME with destination so we can open
      }
      else if(dummy == "usemtl")
      {
        fin>>colorInfo; // name of the color for material
        // start loading the file and get color info from .mtlFile
        if(!LoadMTL(mtlFile, colorInfo)) // check if file exists
        {
          std::cerr<< "ERROR: MTL file not found, colors not extracted.\n";
        }// else colors are saved onto the RGB array
      }
      else if(dummy=="v") // meaning we are at the vertices
      {
        for(int i = 0; i< 3; i++ )// for the three positions
          {
            fin>> Geometry[vertexSize].position[i]; // stores floats to the three positions
            Geometry[vertexSize].color[i] = RGB[i];
          }
        vertexSize++; // go to next vertex
      }
      else if(dummy=="f") // we are at the faces
      {
        int i = 0;
        // extract each character at a time
        while(fin.get(ignore))
        {

          if(ignore == ' ')// check if we are at a space
          {
            fin>>Indices[index]; // grab the first index available and ignore the rest
            if(colorIndex < vertexSize )
            {
              Geometry[colorIndex].color[i] = RGB[i];
            }
            else{
              colorIndex-=1;
            }

            index++; // go to next
            i++;
          }

          if(ignore == '\n')// we are at the end of the face line
          {
            break;
          }


        }// end while
        colorIndex++;

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
  model = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f)); //* glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(1.0,0.0, 0.0));

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
