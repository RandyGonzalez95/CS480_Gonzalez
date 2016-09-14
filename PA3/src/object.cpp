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

  angle = 0.0f;
  currentAngle = 0.0f;
 

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
 
  // Check keyboard input
  if( code == 0 )
  {
    // DEFAULT
    angle += dt * M_PI/1000;
    currentAngle += dt* M_PI/1000;

  }
  // If 'W' is pressed
  else if( code == 1 )
  {
    // REVERSE
    if( !toggle ) // check if key was pressed the first time   
    { 
      angle -= dt * M_PI/1000;  
      currentAngle -= dt* M_PI/1000;
    }       
    else 
    {
      // Normal
      angle += dt* M_PI/1000;
      currentAngle += dt* M_PI/1000;
    }

   
  }
  // If user presses 'E'
  else if( (code == 2) )
  {
    // STOP ROTATE but keep ORBIT
    angle += dt* M_PI/1000;
    currentAngle += dt* M_PI/1000;;

    if(!toggle)// check for toggle key
    {    
      // stop cube from rotate while orbitting     
    	currentAngle = 0;      
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
      angle += dt * M_PI/1000;
      currentAngle += dt * M_PI/1000;          
    }
  }
  // If 'T' is pressed
  else if( code == 4 )
  {
    if(!toggle)// check for toggle key
    {
      // PAUSE ORBIT
      angle += 0;
      currentAngle += dt * M_PI/1000;   

    }
    else
    {  
      // normal setting
      angle += dt * M_PI/1000;
      currentAngle += dt * M_PI/1000;          
    }
  }  



  // Declare matrices
  glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -5.0));
  glm::mat4 rotateMatrix2 = glm::rotate(glm::mat4(1.0f), (currentAngle), glm::vec3(0.0, 1.0, 0.0));

  model = rotateMatrix * translateMatrix * rotateMatrix2;
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

