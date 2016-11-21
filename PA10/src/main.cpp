#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  /*char *objFile;
  char *textureFile;

  // Check for file input in command line
  if(argc != 3) // if no more than two arguments
  {
    printf("ERROR: Provide necessary model files: object, and texture.\n");
    return 1;
  }
  //else save the obj file
  objFile = argv[1];
  textureFile = argv[2];*/

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Pinball", 1024, 650);
  if(!engine->Initialize())// pass object through
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
