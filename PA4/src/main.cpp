#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  char *objFile;

  // Check for file input in command line
  if(argc != 2) // if no more than two arguments
  {
    printf("ERROR: No OBJ file found.\n");
    return 1;
  }
  //else save the obj file
  objFile = argv[1];

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);
  if(!engine->Initialize(objFile)) // pass object through
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
