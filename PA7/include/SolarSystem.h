#include "object.h"
#include "camera.h"
#include "graphics_headers.h"

class SolarSystem
{
public:
  SolarSystem(char* configFile);
  ~SolarSystem();

  bool Initialize(char* filename);
  void Update(unsigned int dt);
  bool configData(char*filename);
  bool readFile(char*filepath);
  Object *getPlanets();
  int getNumObjects();
  void Render();


private:
  Object *Planet;
  Object Sun;
  int numPlanets;

};
