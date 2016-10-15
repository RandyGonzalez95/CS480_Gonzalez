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
  //Object temp(data[2], data[3]);

  // Open configFile
  if(!ReadFile(filename))
  {
    return false;
  }

  /*for(int i = 0; i<SolarData.size(); i++)
  {
    std::cout<<"OBJ: "<<SolarData[i].objFile <<"\n";
    std::cout<<"Tex: "<<SolarData[i].texFile <<"\n";
    std::cout<<"orbit: "<<SolarData[i].oAngle <<"\n";
    std::cout<<"rotate: "<<SolarData[i].rAngle <<"\n";
    std::cout<<"distance: "<<SolarData[i].distance <<"\n";
    std::cout<<"Size: "<<SolarData[i].size <<"\n";

  }*/



  //Planet.push_back(temp);
  return true;

}

void SolarSystem::Update(unsigned int dt, bool *code)
{
  Sun->Update(dt, code);
}

bool SolarSystem::ConfigData(char*filename)
{


}

bool SolarSystem::ReadFile(char*filepath)
{
  char dummy;
  std::ifstream fin(filepath);
  char ignore;
  Data temp;

  std::cout<<filepath<<"\n";
  //check if file exists
  if( !fin.good() )
  {
    std::cerr<< "Config File not found. Ending Program.\n";
    return false;
  }

  while(fin.get(dummy))
  {
    std::cout<<dummy;
    if( dummy == '-')
    {
      fin>>temp.objFile;
      std::cout<<temp.objFile<<"\n";
    }
    if( dummy == ':')
    {
      fin>>temp.texFile;
      std::cout<<temp.texFile<<"\n";

      fin>>temp.rAngle;
      std::cout<<"rAngle: "<<temp.rAngle<<"\n";
      fin>>temp.oAngle;
      std::cout<<"oAngle: "<<temp.oAngle<<"\n";
      fin>>temp.distance;
      std::cout<<"distance: "<<temp.distance<<"\n";
      fin>>temp.size;
      std::cout<<"size: "<<temp.size<<"\n";
      numPlanets++;
    }

    SolarData.push_back(temp);
  }

  std::cout<< "hi";

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
