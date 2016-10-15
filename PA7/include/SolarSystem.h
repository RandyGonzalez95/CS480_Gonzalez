#include "object.h"
#include "camera.h"
#include "graphics_headers.h"

class SolarSystem
{
public:
  SolarSystem(char* configFile);
  ~SolarSystem();

  bool Initialize(char* filename);
  void Update(unsigned int dt, bool *code);
  bool ConfigData(char*filename);
  bool ReadFile(char*filepath);
  Object GetPlanet(int index);
  Object GetMoon(int index);
  Object* GetSun();
  int getNumObjects();



private:
  std::vector<Object> Planet;
  std::vector<Object> Moon;
  Object *Sun;
  int numPlanets;
  std::vector<Data> SolarData;

};
