#Randy Gonzalez
#CS 480- Graphics
#PA4 Compiling Instructions

To compile the program, make a new directory, name it build
cd build
Under the build directory type
cmake ..
Then type
make

To run executable, remain under build directory and type
./Tutorial ../Object/box.obj
This last line runs the executable and it is crucial for the path of the object to be passed in.
box.obj is already provided but any arbitrary file name may be used as long as
the path is specified.
Program should execute accordingly.

#NOTE
Extra credit was attempted in this assignment but not executed effectively. The corresponding
mtl file is provided for the box.obj file. MTL should NOT be passed under the command line.
If testing a different obj file than the one provided make sure its corresponding mtl file is
placed under the Material folder.(optional) 

#Shader files are under /PA4/shaders directory.
