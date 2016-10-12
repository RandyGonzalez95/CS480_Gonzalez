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

void SolarSystem::Update(unsigned int dt, bool *code)
{


}
bool SolarSystem::configData(char*filename)
{

}

bool SolarSystem::readFile(char*filepath)
{

}

Object SolarSystem::GetPlanet(int index)
{

  return Planet[index];
}

Object SolarSystem::GetMoon()
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
