#include "object.h"
#include "camera.h"
#include "graphics_headers.h"

class SolarSystem
{
public:
  SolarSystem(char* configFile);
  ~SolarSystem();

  bool Initialize(char* filename);
  void Update(unsigned int dt, int code);
  bool ReadFile(char*filepath);
  Object GetPlanet(int index);
  Object GetMoon(int index);
  Object* GetSun();
  int getNumObjects();
  glm::mat4 GetView();



private:
  std::vector<Object> Planet;
  std::vector<Object> Moon;
  Object *Sun;
  int numPlanets;
  std::vector<Data> SolarData;
  glm::mat4 viewMatrix;

};
