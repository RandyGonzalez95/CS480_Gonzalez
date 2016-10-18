#include "object.h"
#include <fstream>
#include <cstring>

Object::Object()
{
  rotateAngle = 0;
  orbitAngle = 0;
  moonAngle = new float[2];
  moonAngle[0] = 0; // rotateAngle
  moonAngle[1] = 0; // orbit


}

Object::~Object()
{
  Geometry.clear();
  Indices.clear();
}

bool Object::Initialize()
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
  int index = 0;
  Vertex temp;

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
        // Grab index info of the faces
        index = model->mFaces[iFaces].mIndices[i];

        // check for texture coodinates
        if(model->HasTextureCoords(0))
        {
          temp.uv[0] = model->mTextureCoords[0][index].x;
          temp.uv[1] = 1-model->mTextureCoords[0][index].y;
        }

        // Load Vertex Position
        for(int j = 0; j < 3; j++)  // iterate through each face
        {
          // Index info corresponds to a vertex position
          temp.position[j] = model->mVertices[index][j];
        }

        // Push back Index and Geomtry info
        Indices.push_back(index);
        Geometry.push_back(temp);
      }
    }
  }
}

void Object::Update(unsigned int dt, bool* code, Data SolarData)
{
  orbitAngle += SolarData.oAngle;
  rotateAngle += SolarData.rAngle;



  // Declare matrices
  glm::mat4 orbitRotation = glm::rotate(glm::mat4(1.0f), orbitAngle, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(distance, 0.0, 0.0));
  glm::mat4 spinRotation = glm::rotate(glm::mat4(1.0f), rotateAngle, glm::vec3(0.0, 1.0, 0.0));


  model = ( orbitRotation * translateMatrix* spinRotation) * glm::scale(glm::mat4(1.0f), glm::vec3(size / 10));

  orbitRotation = glm::rotate(model, rotateAngle, glm::vec3(0.0, 1.0, 0.0));
  translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -1.5));
  spinRotation = glm::rotate(glm::mat4(1.0f), orbitAngle, glm::vec3(0.0, 1.0, 0.0));

  // Moon Model
  moonModel = (orbitRotation * translateMatrix * spinRotation) * glm::scale(glm::mat4(1.0f), glm::vec3(0.15));;


}

int Object::GetNumMoons()
{

  return numMoons;
}

glm::mat4 Object::GetModel()
{
  //model = glm::scale(glm::mat4(1.0f), glm::vec3(6.0)) * glm::rotate(glm::mat4(1.0f), (180.0f), glm::vec3(1.0, 0.0, 0.0));
  return model;
}

glm::mat4 Object::GetMoon()
{

  return moonModel;
}

void Object::SetData(Data SolarData)
{
  // Init All data
  rotateAngle = SolarData.rAngle;
  orbitAngle = SolarData.oAngle;
  distance = SolarData.distance;
  size = SolarData.size;
  objFile= SolarData.objFile;
  textureFile = SolarData.texFile;
  numMoons = SolarData.numberMoons;

  // Initialize
  myScene = NULL;

  orbitAngle = 0;

  // Open File Data
  if(!Initialize())
  {
    std::cerr<< "OBJ file was not found, ending program.\n";
    exit(1);
  }

  SetVertices();
  getTextures();

  // Draw
  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Geometry.size(), &Geometry[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

void Object::getTextures()
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

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);


  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Object::RenderSaturn()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, Textures);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);


  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
