#include "graphics.h"

Graphics::Graphics()
{
  x = 0;
  y = 55;
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

  // Set Camera
  SetCamera(codes);

  // Check Game Logic
  PlayGame(codes);

  // Update all items that aren't the table
  for(int i = 0; i < physicsWorld->getObjects().size() - 5; i++)
  {
    // Update all objects in the world
    physicsWorld->getObject(i)->Update();

    // Get the velocity of the objects
    btVector3 vel = physicsWorld->getObject(i)->getRigidBody()->getLinearVelocity();
    physicsWorld->getObject(20)->SetLocation(theta_y, physicsWorld->getObject(0));
    //physicsWorld->getObject(20)->UpdateStick(xForce, zForce, physicsWorld->getObject(0));

    // If the velocity is moving upwards reset it to 0 to keep objects on table
    if(vel.getY() > 0)
    {
      vel.setY(0);
    }

    // Set the linear velocity of the object
    physicsWorld->getObject(i)->getRigidBody()->setLinearVelocity(vel);
  }
}

void Graphics::PlayGame(bool codes[])
{

  // Hit the cue ball
  if(codes[6]) // Space bar
  {
    physicsWorld->getObject(0)->getRigidBody()->setLinearVelocity(btVector3(xForce, 0.0f, zForce));

    codes[6] = false;
  }

  // Reset the game
  if(codes[7]) // 'P'
  {
    physicsWorld = new Physics();

    codes[7] = false;
  }

  // Move pool stick left
  if(codes[8])
  {
    theta_y+= .05;

    if(zForce == 90)
    {
      positiveZ = false;
      xForce += 180;
    }

    else if(zForce == -90)
    {
      positiveZ = true;
      xForce -= 180;
    }

    if(positiveZ)
    {
      zForce  += 5;
    }

    else
    {
      zForce -= 5;
    }


    codes[8] = false;
  }

  // Move pool stick right
  if(codes[9])
  {

    theta_y -= .05;

    if(zForce == 90)
    {

      positiveZ = true;
      xForce -= 180;
    }

    else if(zForce == -90)
    {
      positiveZ = false;
      xForce += 180;
    }

    if(positiveZ)
    {
      zForce -= 5;
    }

    else
    {
      zForce += 5;
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
