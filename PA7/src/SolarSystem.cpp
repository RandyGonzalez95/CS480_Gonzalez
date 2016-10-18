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
  delete Sun;
  Planet.clear();
  Moon.clear();

}

bool SolarSystem::Initialize(char* filename)
{
  // Temporary object to allocate data
  Object *temp = new Object;
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
    temp->SetData(SolarData[i]);
    // Set planet data
    Planet.push_back(*temp);

    if(i==SolarData.size())
    {
      Moon.push_back(*temp);
    }
  }

  return true;
}

void SolarSystem::Update(unsigned int dt, int code)
{
  // Update the Sun
  Sun->Update(dt, SolarData[0]);
  // Update each Planet
  for(int i = 1; i <= numPlanets; i++)
  {
    Planet[i-1].Update(dt, SolarData[i]);
  }

  glm::mat4 sunModel = Sun->GetModel();

  glm::vec3 CameraFocus = glm::vec3( sunModel * glm::vec4(0.0, 0.0, 0.0, 1.0));

  glm::vec3 CameraPosition = CameraFocus + glm::vec3( 0.0, .5, -.5 );
  if(code == 0)
  {

  viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position X, Y, Z
                              glm::vec3(0.0, 0.0, 0.0), //Focus point
                              glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  }
  if(code == 1)
  {
    viewMatrix = glm::lookAt( CameraPosition, //Eye Position X, Y, Z
                              CameraFocus, //Focus point
                              glm::vec3(0.0, 0.0, 1.0)); //Positive Y is up

  }

  if(code == 2)
  {
    viewMatrix = glm::lookAt( glm::vec3(-20.0, 8.0, -20.0), //Eye Position X, Y, Z
                              glm::vec3(0.0, 0.0, 0.0), //Focus point
                              glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  }
  if(code == 3)
  {
    viewMatrix = glm::lookAt( glm::vec3(0.0, -20.0, -20.0), //Eye Position X, Y, Z
                              glm::vec3(0.0, 0.0, 0.0), //Focus point
                              glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  }
  if(code == 4)
  {
    viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position X, Y, Z
                              glm::vec3(0.0, 0.0, 0.0), //Focus point
                              glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  }
  if(code == 5)
  {
    viewMatrix = glm::lookAt( glm::vec3(0.0, 8.0, -20.0), //Eye Position X, Y, Z
                                  glm::vec3(0.0, 0.0, 0.0), //Focus point
                                  glm::vec3(0.0, 1.0, 0.0));

  }
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

  while(fin.get(dummy))
  {
    if( dummy == ':')
    {
      fin>>temp.texFile;
      fin>>temp.objFile;
      fin>>temp.rAngle;
      fin>>temp.oAngle;
      fin>>temp.distance;
      fin>>temp.size;
      fin>>temp.numberMoons;

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
