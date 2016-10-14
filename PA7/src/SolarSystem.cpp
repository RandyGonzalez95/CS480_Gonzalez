#include "SolarSystem.h"

SolarSystem::SolarSystem(char* configFile)
{


  if(!Initialize(configFile))
  {

    exit(1);
  }

  numPlanets = 9;



}

SolarSystem::~SolarSystem()
{


}

bool SolarSystem::Initialize(char* filename)
{
  //Object temp(data[2], data[3]);

  // Open configFile
  if(!ReadFile(filename))
  {

    return false;
  }

  Sun = new Object(data[0], data[1]);


  //Planet.push_back(temp);


}

void SolarSystem::Update(unsigned int dt, bool *code)
{


}
bool SolarSystem::ConfigData(char*filename)
{


}

bool SolarSystem::ReadFile(char*filepath)
{
  std::string temp;
  std::ifstream fin(filepath);

  //check if file exists
  if( !fin.good() )
  {
    std::cerr<< "Config File not found. Ending Program.\n";
    return false;
  }

  while(fin>>temp)
  {
    data.push_back(temp);
  }


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

Object SolarSystem::GetSun()
{


}

int SolarSystem::getNumObjects()
{

  return numPlanets+1;
}
