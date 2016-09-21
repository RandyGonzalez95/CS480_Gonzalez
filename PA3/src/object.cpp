#include "object.h"

Object::Object()
{
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

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
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
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  // Initialize Angle Arrays
  planetAngle = new float[2];
  moonAngle = new float[2];

  for(unsigned int i = 0; i<2; i++ )
  {
    planetAngle[i] = 0;
    moonAngle[i] = 0;
  }


  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, bool *code)
{

  // If 'Q' is pressed
  if( code[0] ) // Reverse Orbit
  {
     planetAngle[0] -= dt * M_PI/600;  //orbit
     planetAngle[1] += dt * M_PI/600; // rotate
  }
  // If 'W' is pressed
  if( code[1] ) // Reverse Rotate
  {
      planetAngle[1] -= dt* M_PI/250;  // rotate

      if(!code[7]) // if the moon is not paused
      moonAngle[0] += (dt * M_PI/400);
  }
  // If 'E' is pressed
  if( code[2] && !code[7])
  {
    // don't do anything

    moonAngle[0] += (dt * M_PI/1000); // orbit
    moonAngle[1] += (dt * M_PI/1000); // rotate
  }
  // If user presses 'R'
  if( code[3] )  // PAUSE rotate, orbit in place
  {
    planetAngle[1] -= dt * M_PI/1000;   // stop rotate angle
  }
  // If 'T' is pressed
  if( code[4] )
  {
    // PAUSE orbit, orbit around origin
    planetAngle[0] -= dt * M_PI/1000;   // stop orbit angle
    if( code[0] )// if it's reverse
    {
      planetAngle[0] += dt * M_PI/600;
    }
  }
  // Moon Interactions
  // If 'A' is pressed
  if( code[5] )// Reverse Orbit of Moon
  {
    moonAngle[0] -= dt * M_PI/250; // orbit
    moonAngle[1] += dt * M_PI/250; // rotate
  }
  // If 'S' is pressed
  if( code[6] ) // Reverse Rotate
  {
    moonAngle[1] -= dt * M_PI/200; // rotate
  }
  // If 'D' is pressed
  if( code[7] ) // Pause completely
  {
    // do nothing
  }
  // If user presses 'F'
  if( code[8] )  // PAUSE rotate for moon
  {
    moonAngle[0] += dt*M_PI/600; // pauses orbit angle
  }
  // If 'G' is pressed
  if( code[9] ) // PAUSE orbit
  {
    moonAngle[1] += dt*M_PI/600; // pauses rotate angle
  }
  // Default
  if(!code[2]) // do if NOT paused
  {
    // plant orbit and rotate
    planetAngle[0] += dt * M_PI/1000; // orbit
    planetAngle[1] += dt * M_PI/1000; // rotate

  }
  if(!code[7]) // if not paused
  {
    // orbit moon angle
    moonAngle[0] += (dt * M_PI/1000); // orbit
    moonAngle[1] += (dt * M_PI/1000); // rotate
  }


  // Declare matrices
  glm::mat4 orbitMatrix = glm::rotate(glm::mat4(1.0f), (planetAngle[0]), glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -5.0));
  glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), (planetAngle[1]), glm::vec3(0.0, 1.0, 0.0));

  // Planet Model
  model = orbitMatrix * translateMatrix * rotateMatrix; // planet

  // Moon matrices
  orbitMatrix = glm::rotate(model, (moonAngle[0]), glm::vec3(0.0, 1.0, 0.0));
  translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0));
  rotateMatrix = glm::rotate(glm::mat4(1.0f), (moonAngle[1]), glm::vec3(0.0, 1.0, 0.0));

  // Moon Model
  moon_model = (orbitMatrix * translateMatrix * rotateMatrix) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5));;


}

glm::mat4 Object::GetModel()
{
  return model;
}

glm::mat4 Object::GetMoonModel()
{
  return moon_model;
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
