#include "graphics.h"

Graphics::Graphics()
{
  x = 0;
  y = 75;
  z = 57;
}

Graphics::~Graphics()
{
  delete m_camera;
  delete m_shader;
  delete physicsWorld;
  physicsWorld = NULL;
  m_camera = NULL;
  m_shader = NULL;
}

bool Graphics::Initialize(int width, int height, bool flag)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)

    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }

  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();

  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Create board
  physicsWorld = new Physics();

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER, flag))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER, flag))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shadersphere
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Locate the Light Position
  m_LightPosition = m_shader->GetUniformLocation("LightPosition");
  if (m_LightPosition == INVALID_UNIFORM_LOCATION)
  {
    printf("m_LightPosition not found\n");
    return false;
  }

  // Locate Ambient lighting location
  m_AmbientProduct = m_shader->GetUniformLocation("AmbientProduct");
  if (m_AmbientProduct == INVALID_UNIFORM_LOCATION)
  {
    printf("m_AmbientProduct not found\n");
    return false;
  }

  // Locate Diffuse Lighting Location
  m_DiffuseProduct = m_shader->GetUniformLocation("DiffuseProduct");
  if (m_DiffuseProduct == INVALID_UNIFORM_LOCATION)
  {
    printf("m_DiffuseProduct not found\n");
    return false;
  }

  // Locate Specular Lighting
  m_SpecularProduct = m_shader->GetUniformLocation("SpecularProduct");
  if (m_SpecularProduct == INVALID_UNIFORM_LOCATION)
  {
    printf("m_SpecularProduct not found\n");
    return false;
  }

  // get ShininessAddShader
  m_shininess= m_shader->GetUniformLocation("Shininess");
  if (m_shininess == INVALID_UNIFORM_LOCATION)
  {
    printf("m_shininess not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;

}

void Graphics::Update(unsigned int dt, bool codes[])
{
  // Start Physics Step Simulation
  simTime = 0.0083;
  physicsWorld->getWorld()->stepSimulation(simTime, 10);

  btTransform ballTrans;
  btVector3 ballPos;

  // Set Camera
  SetCamera(codes);

  // Check Game Logic
  PlayGame(codes);

  // Change Light stuff
  ChangeLight(codes);

  // Update all items that aren't the table
  for(int i = 0; i < 17; i++)
  {
    // Update the object in the world
    physicsWorld->getObject(i)->Update();

    // Get the velocity of the object
    btVector3 vel = physicsWorld->getObject(i)->getRigidBody()->getLinearVelocity();

    // If cue ball is now static we may shoot again.
    if( (i == 0) && 
        (vel.length() < 0.5))
        {
          shot = false;
          vel.setX(0);
          vel.setZ(0);
        }

    // Move stick to location of cue ball and current theta
    if(!shot)
    {
      physicsWorld->getObject(20)->SetLocation(theta_y, physicsWorld->getObject(0));
    }

    // Get the objects location
    physicsWorld->getObject(i)->getRigidBody()->getMotionState()->getWorldTransform(ballTrans);
    ballPos = ballTrans.getOrigin();

    // Check if the ball has been made into a pocket
    if(ballPos.getY() < 0.0 && physicsWorld->getObject(i)->madeIn == false)
    {
      // If the cue has been made reset it
      if(i == 0 && !outputCue)
      {
        std::cout << "The cue ball was hit in, resetting the cue ball now." << std::endl;
        physicsWorld->getObject(0)->ResetCue();
        outputCue = true;
      }

      // If the 8 ball has been made end game
      else if(i == 8)
      {
        codes[7] = true;
        std::cout << "The " << i << " ball was hit in. ";
        std::cout << "End of game, restarting" << std::endl;
      }

      // If a solid has been made output this information to the user
      else if(i < 8 && !outputCue)
      {
        physicsWorld->getObject(i)->madeIn = true;
        std::cout << "The " << i << " ball was hit in. ";
        std::cout << "This ball is solid." << std::endl;
      }

      // Else a striped has been made, output this to user
      else if(!outputCue)
      {
        physicsWorld->getObject(i)->madeIn = true;
        std::cout << "The " << i << " ball was hit in. ";
        std::cout << "This ball is striped." << std::endl;
      }
    }

    // If the velocity is moving upwards reset it to 0 to keep objects on table
    if(vel.getY() > 0)
    {
      vel.setY(0);
    }

    // Set the linear velocity of the object
    physicsWorld->getObject(i)->getRigidBody()->setLinearVelocity(vel);
  }
}

void Graphics::ChangeLight(bool codes[])
{
  if(codes[10]) // Decrease Ambient
  {
    light -= 0.1;
    codes[10] = false;
  }

  if(codes[11]) // Increase Ambient
  {
    light += 0.1;
    codes[11] = false;
  }

  if(codes[12]) // Decrease Specular
  {
    light2 -= 0.5;
    codes[12] = false;
  }

  if(codes[13]) // Increase Specular
  {
    light2 +=0.5;
    codes[13] = false;
  }
}

void Graphics::PlayGame(bool codes[])
{
  if(codes[6] && !shot ) // Hit the cue ball with the pool stick
  {
    // Set flags that the cue ball has been hit
    outputCue = false;
    shot = true;

    // Unrender the pool stick
    physicsWorld->getObject(20)->unrenderPoolStick();

    // Give the cue ball the velocity specified by the user
    physicsWorld->getObject(0)->getRigidBody()->setLinearVelocity(btVector3(xForce, 0.0f, zForce));

    // Reset all values for force
    theta_y = 0;
    xForce = -89;
    zForce = -1;
    lpositiveX = false;
    lpositiveZ = true;
    rpositiveX = true;
    rpositiveZ = false;

    codes[6] = false;
  }

  else // Else user is trying to shoot the ball while it is moving
  {
      codes[6] = false;
  }

  if(codes[7]) // Reset the game
  {
    physicsWorld = new Physics();

    codes[7] = false;
  }

  if(codes[8]) // Move pool stick left
  {
    // Update model of pool stick
    theta_y+= .01693;

    // Move the x positive
    if(lpositiveX)
    {
      xForce  += 1.0;
    }

    // Else move the x negative
    else
    {
      xForce -= 1.0;
    }

    // Move the z positive
    if(lpositiveZ)
    {
      zForce  += 1.0;
    }

    // Else move the z negative
    else
    {
      zForce -= 1.0;
    }

    // If zForce is 90 set flags
    if(zForce == 90)
    {
      lpositiveX = true;
      lpositiveZ = false;
      rpositiveX = false;
      rpositiveZ = true;
    }

    // Else if zForce is -90 set flags
    else if(zForce == -90)
    {
      lpositiveX = false;
      lpositiveZ = true;
      rpositiveX = true;
      rpositiveZ = false;
    }

    // Else if xForce is 90 set flags
    if(xForce == 90)
    {
      lpositiveX = false;
      lpositiveZ = false;
      rpositiveX = true;
      rpositiveZ = true;
    }

    // Else if xForce is -90 set flags
    else if(xForce == -90)
    {
      lpositiveZ = true;
      lpositiveX = true;
      rpositiveX = false;
      rpositiveZ = false;
    }

    codes[8] = false;
  }

  if(codes[9]) // Move pool stick right
  {
    // Update model of pool stick
    theta_y -= .01693;

    // Move the z positive
    if(rpositiveX)
    {
      xForce += 1.0;
    }

    // Else move the x negative
    else
    {
      xForce -= 1.0;
    }

    // Move the z positive
    if(rpositiveZ)
    {
      zForce += 1.0;
    }

    // Else move the z negative
    else
    {
      zForce -= 1.0;
    }

    // If zForce is 90 set flags
    if(zForce == 90)
    {
      rpositiveX = false;
      rpositiveZ = false;
      lpositiveX = true;
      lpositiveZ = true;
    }

    // If zForce is -90 set flags
    else if(zForce == -90)
    {
      rpositiveX = true;
      rpositiveZ = true;
      lpositiveX = false;
      lpositiveZ = false;
    }

    // If xForce is 90 set flags
    if(xForce == 90)
    {
      rpositiveX = false;
      rpositiveZ = true;
      lpositiveX = true;
      lpositiveZ = false;
    }

    // If xForce is -90 set flags
    else if(xForce == -90)
    {
      rpositiveZ = false;
      rpositiveX = true;
      lpositiveZ = true;
      lpositiveX = false;
    }
    
    codes[9] = false;
  }
}

void Graphics::SetCamera(bool codes[])
{
  if(codes[0]) // Move X Up
  {
    x += 1;
    codes[0] = false;
  }

  if(codes[1]) // Move Y Up
  {
    y += 1;
    codes[1] = false;
  }

  if(codes[2]) // Move Z Up
  {
    z += 1;
    codes[2] = false;
  }

  if(codes[3]) // Move X Down
  {
    x -= 1;
    codes[3] = false;
  }

  if(codes[4]) // Move Y Down
  {
    y -= 1;
    codes[4] = false;
  }

  if(codes[5]) // Move Z Down
  {
    z -= 1;
    codes[5] = false;
  }

  if(codes[14]) // reset view
  {
    x = 0;
    y = 75;
    z = 57;
    codes[14] = false;
  }
  
  // Set camera view
  m_camera->SetView(x, y, z);
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  // Render the all objects on Pool Table
  for(int i = 0; i < physicsWorld->getObjects().size(); i++)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr( physicsWorld->getObject(i)->GetModel()));
    physicsWorld->getObject(i)->Render();
  }

  // Lights
  glUniform4fv(m_LightPosition, 1, glm::value_ptr(m_camera->GetView()));
  glUniform4fv(m_AmbientProduct, 1, glm::value_ptr(glm::vec3(light)));
  //glUniform4fv(m_DiffuseProduct, 1, glm::value_ptr(glm::vec3(0.5) ));
  glUniform4fv(m_SpecularProduct, 1, glm::value_ptr(glm::vec4(glm::vec3(light2), 0.0)));

  // Get any errors from OpenGL
  auto error = glGetError();
  if (error != GL_NO_ERROR)
  {
    std::string val = ErrorString(error);
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
