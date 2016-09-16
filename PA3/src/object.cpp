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

void Object::Update(unsigned int dt, int &code, bool &toggle, bool &resetKey)
{ 
  // orbit moon angle
  moonAngle[0] += (dt * M_PI/1000);
  moonAngle[1] += (dt * M_PI/1000);

  // Check keyboard input
  if( code == 0 )
  {
    // DEFAULT
    planetAngle[0] += dt * M_PI/1000; // orbit
    planetAngle[1] += dt* M_PI/1000; // rotate
   

  }
  // If 'W' is pressed
  else if( code == 1 )
  {
    // REVERSE
    if( !toggle ) // check if key was pressed the first time   
    { 
      planetAngle[0] -= dt * M_PI/1000;  //orbit
      planetAngle[1] -= dt* M_PI/1000;  // rotate

      moonAngle[0] -= (dt * M_PI/1000);
      moonAngle[1] -= (dt * M_PI/1000);
    }       
    else 
    {
      // Normal
      planetAngle[0] += dt* M_PI/1000;  // orbit
      planetAngle[1] += dt* M_PI/1000;  // rotate

      moonAngle[0] += (dt * M_PI/1000);
      moonAngle[1] += (dt * M_PI/1000);
    }

   
  }
  // If user presses 'E'
  else if( (code == 2) )
  {
    // STOP ROTATE but keep ORBIT
    planetAngle[0] += dt* M_PI/1000; // orbit
    planetAngle[1] += dt* M_PI/1000; // rotate

    if(!toggle)// check for toggle key
    {    
      // stop cube from rotate while orbitting     
    	planetAngle[1] = 0;   // rotate   
    }

   
  }
  // If 'R' is pressed
  else if( code == 3 )
  {
    if(!toggle)// check for toggle key
    {    
      // PAUSE CUBE	
	// do nothing
    }
    else
    {  
      // Normal
      planetAngle[0] += dt * M_PI/1000; // orbit
      planetAngle[1] += dt * M_PI/1000; // rotate         
    }
  }
  // If 'T' is pressed
  else if( code == 4 )
  {
    if(!toggle)// check for toggle key
    {
      // PAUSE ORBIT
      planetAngle[0] += 0; // orbit
      planetAngle[1] += dt * M_PI/1000; // rotate  

    }
    else
    {  
      // normal setting
      planetAngle[0] += dt * M_PI/1000; // orbit
      planetAngle[1] += dt * M_PI/1000;  // rotate        
    }
  }  



  // Declare matrices
  glm::mat4 orbitMatrix = glm::rotate(glm::mat4(1.0f), (planetAngle[0]), glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -5.0));
  glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), (planetAngle[1]), glm::vec3(0.0, 1.0, 0.0));

 // model = glm::translate(glm::mat4(1.0f), glm::vec3(5*sin(planetAngle[0]), 0.0, 5*cos(planetAngle[1])));
  //model = glm::rotate(model, (planetAngle[1]), glm::vec3(0.0, 1.0, 0.0));;

  model = orbitMatrix * translateMatrix * rotateMatrix; // planet
 

  // Moon matrices

  orbitMatrix = glm::rotate(model, (moonAngle[0]), glm::vec3(0.0, 1.0, 0.0));
  translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -3.0));
  rotateMatrix = glm::rotate(glm::mat4(1.0f), (moonAngle[1]), glm::vec3(0.0, 1.0, 0.0));

  moon_model = orbitMatrix * translateMatrix * rotateMatrix;

  /*moon_model = glm::rotate(glm::mat4(1.0f), (moonAngle[0]), glm::vec3(0.0, 1.0, 0.0));    
  moon_model = glm::translate( model, glm::vec3( 0.0, 0.0, -3.0));   
  moon_model = glm::rotate(moon_model, moonAngle[1], glm::vec3(0.0,1.0,0.0));*/

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

