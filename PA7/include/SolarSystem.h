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
  bool configData(char*filename);
  bool readFile(char*filepath);
  Object GetPlanet(int index);
  Object GetMoon(int index);
  Object GetSun();
  int getNumObjects();



private:
  Object *Planet;
  Object *Moon;
  Object Sun;
  int numPlanets;

};
