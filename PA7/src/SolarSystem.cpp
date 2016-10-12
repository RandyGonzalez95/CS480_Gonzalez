#include "SolarSystem.h"

SolarSystem::SolarSystem(char* configFile)
{
  numPlanets = 9;

  Initialize(configFile);



}

SolarSystem::~SolarSystem()
{


}

bool SolarSystem::Initialize(char* filename)
{
  // Open configFile



}

void SolarSystem::Update(unsigned int dt)
{


}
bool SolarSystem::configData(char*filename)
{

}

bool SolarSystem::readFile(char*filepath)
{

}

Object* SolarSystem::getPlanets()
{


}

int SolarSystem::getNumObjects()
{

  return numPlanets+1;
}

void SolarSystem::Render()
{
  for(int i = 0; i<numPlanets; i++)
  {

  }

}
