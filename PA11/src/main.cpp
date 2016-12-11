#include "engine.h"

int main(int argc, char **argv)
{
  // Start the engine
  Engine *engine = new Engine("Pool", 1024, 800);

  // If engine did not initialize correctly end program
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }

  // Run Engine
  engine->Run();

  delete engine;
  engine = NULL;

  return 0;
}
