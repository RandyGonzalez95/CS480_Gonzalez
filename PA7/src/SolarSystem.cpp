#include "SolarSystem.h"

SolarSystem::SolarSystem(char* configFile)
{
  numPlanets = 0;

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

  // Last Element of solar data contains moon info.
  // only store planet data in planet vector
  // Loop Through number of planets and set the data
  for(int i = 1; i<SolarData.size() ;i++)
  {
    temp->SetData(SolarData[i]);
    // Set planet data
    Planet.push_back(*temp);

    if( i == SolarData.size())
    {
      // Create the moon object and initialize it with data
      Moon.push_back(*temp);
    }
  }

  return true;
}

void SolarSystem::Update(unsigned int dt, bool *code)
{


    if(code[0])
    {
    

    }
    if(code[1])
    {


    }

    if(code[2])
    {


    }
    if(code[3])
    {


    }

  // Update the Sun
  Sun->Update(dt, code, SolarData[0]);
  // Update each Planet
  for(int i = 1; i <= numPlanets; i++)
  {
    Planet[i-1].Update(dt, code, SolarData[i]);
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
