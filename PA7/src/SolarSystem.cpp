#include "SolarSystem.h"

SolarSystem::SolarSystem(char* configFile)
{
  // Default settings
  numPlanets = 0;
  viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position
                      glm::vec3(0.0, 0.0, 0.0), //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  // Initialize the Solar System with the configuration file
  if(!Initialize(configFile))
  {
    // If initialize went bad, exit the program
    exit(1);
  }

}

SolarSystem::~SolarSystem()
{
  // deallocate
  delete Sun;
  Planet.clear();
  Moon.clear();

}

bool SolarSystem::Initialize(char* filename)
{
  // Temporary object to allocate data
  int lastIndex = 0;

  // Open configFile
  if(!ReadFile(filename))
  {
    return false;
  }

  // Create the sun and initialize it with data
  Sun = new Object();
  Sun->SetData(SolarData[0]);// first element contains the sun info

  // only store planet data in planet vector
  // Loop Through number of planets and set the datA
  for(int i = 1; i<SolarData.size() ;i++)
  {
    // create temporary object to store all data
    Object *temp = new Object;
    temp->SetData(SolarData[i]);

    // check if we are at the moon data
    if(i==SolarData.size()-1)
    {
      // push moon data back
      Moon.push_back(*temp);
      break;
    }

    // Set planet data
    Planet.push_back(*temp);

  }

  return true;
}

void SolarSystem::Update(unsigned int dt, int code, int speedValue)
{
  // Declare camera variables to move
  glm::vec3 CameraFocus = glm::vec3( (glm::mat4(1.0f) * glm::vec4(0.0, 0.0, 0.0, 1.0)));
  glm::vec3 CameraPosition = CameraFocus + glm::vec3( 0.0, .5, -.5 );

  // To get matrix models
  glm::mat4 SunModel = Sun->GetModel();
  glm::mat4 PlanetModel = glm::mat4(1.0f);


  // Update the Sun
  Sun->Update(dt, SolarData[0], speedValue);
  // Update each Planet
  for(int i = 1; i <= numPlanets; i++)
  {
    Planet[i-1].Update(dt, SolarData[i], speedValue);
  }

  if(code==0) // Default
  {
    viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    speedValue = 1;
    return;

  }
  if(code == 1) // Sun
  {
    // Grab Sun Model to map to camera
    CameraFocus = glm::vec3( SunModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3(0.0, 0.5, -7.5 );


  }
  if(code == 2) // Mercury
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[0].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, .1, -.5 );

  }

  if(code == 3) // Venus
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[1].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, 0.1, -0.5 );

  }
  if(code == 4) // Earth
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[2].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, 0.1 , -0.5 );

  }
  if(code == 5) // Mars
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[3].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, .1, -.5 );

  }
  if(code == 6) // Jupiter
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[4].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, .1, -1.5 );

  }
  if(code == 7) // Saturn
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[5].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, .1, -1.5 );

  }
  if(code == 8) // Uranus
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[6].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, 0.1, -1.5 );

  }
  if(code == 9) // Neptune
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[7].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, .5, -1.5 );

  }
  if(code == 10) // Pluto
  {
    // Grab Planet Model to map to camera
    PlanetModel = Planet[8].GetModel();
    CameraFocus = glm::vec3( PlanetModel * glm::vec4(0.0, 0.0, 0.0, 1.0));
    CameraPosition = CameraFocus + glm::vec3( 0.0, .5, -.2 );

  }
  if(code == 11) // Speed UP
  {
    viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
    return;

  }
  if(code == 12) // Speed Down
  {
    viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position
                        glm::vec3(0.0, 0.0, 0.0), //Focus point
                        glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    return;
  }
  if(code == 13)
  {
      // STILL DO TO

  }

  // Change camera view
  viewMatrix = glm::lookAt( CameraPosition, //Eye Position X, Y, Z
                            CameraFocus, //Focus point
                            glm::vec3(0.0, 0.0, 1.0)); //Positive Y is up
}

bool SolarSystem::ReadFile(char*filepath)
{
  char dummy;
  std::ifstream fin(filepath);
  char ignore;
  Data temp;

  //check if file exists
  if( !fin.good() )
  {
    std::cerr<< "Config File not found. Ending Program.\n";
    return false;
  }

  // run through data file
  while(fin.get(dummy))
  {
    // check if we are at valuable data
    if( dummy == ':')
    {
      fin>>temp.texFile;
      fin>>temp.objFile;
      fin>>temp.rAngle;
      fin>>temp.oAngle;
      fin>>temp.distance;
      fin>>temp.size;
      fin>>temp.numberMoons;

      // push all data back to the struct
      SolarData.push_back(temp);

      numPlanets++;
    }
  }

  numPlanets -= 2;  // minus moon and sun

  return true;
}

Object SolarSystem::GetPlanet(int index)
{
  return Planet[index];
}

Object SolarSystem::GetMoon(int index)
{
  return Moon[index];
}

Object* SolarSystem::GetSun()
{
  return Sun;
}

int SolarSystem::getNumObjects()
{

  return numPlanets+1;
}

glm::mat4 SolarSystem::GetView()
{
  return viewMatrix;
}
