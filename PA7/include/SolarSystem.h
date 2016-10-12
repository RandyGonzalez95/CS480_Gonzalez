#include "object.h"
#include "camera.h"
#include "graphics_headers.h"

class SolarSystem
{
public:
  SolarSystem();
  ~SolarSystem();

  bool Initialize(char* filename);
  void Update(unsigned int dt);
  bool configData(char*filename);
  bool readFile(char*filepath);
  Object *getPlanets();



private:
  Object *Planet;
  Object Sun;
  int numPlanets;

};
