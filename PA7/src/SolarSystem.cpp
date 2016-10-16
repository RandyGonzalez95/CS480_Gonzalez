#include "SolarSystem.h"

SolarSystem::SolarSystem(char* configFile)
{
  numPlanets = 0;

  if(!Initialize(configFile))
  {

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

  Object *temp = new Object;

  // Open configFile
  if(!ReadFile(filename))
  {
    return false;
  }

  Sun = new Object();
  Sun->SetData(SolarData[0]);



  std::cout<< "Number of planets are: "<< numPlanets<<'\n';
  for(int i = 1; i<SolarData.size();i++)
  {
    temp->SetData(SolarData[i]);
    Planet.push_back(*temp);

  }

  return true;
}

void SolarSystem::Update(unsigned int dt, bool *code)
{
  Sun->Update(dt, code);
  for(int i = 0; i < numPlanets; i++)
  {
    Planet[i].Update(dt, code);
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

    if( dummy == '-')
    {
      fin>>temp.objFile;

    }
    if( dummy == ':')
    {
      fin>>temp.texFile;
      fin>>temp.rAngle;
      fin>>temp.oAngle;
      fin>>temp.distance;
      fin>>temp.size;
      numPlanets++;
      SolarData.push_back(temp);
    }
  }

  numPlanets -=2;  // minus moon and sun

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
