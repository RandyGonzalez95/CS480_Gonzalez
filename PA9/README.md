# PA9: Lighting 

## Team Members
- Brett Knadle  
- Phillip Vong  
- Randy Gonzalez  

## Objective:
- Create multiple shaders to do per vertex lighting and per fragment lighting.

#Assignment:
- Building upon PA8, add per-vertex lighting and per-fragment lighting.
	- Make these hader programs wappable on some keystroke.
- Add a spotlight that can follow the sphere around as the sphere moves.
- Have the ability to adjust parameters of lighting.
	- Ambient brightness.
	- Specular brightness of specific objects.
	- Spotlight size and brightness.

## Dependencies, Building, and Running
This program only runs if a object file path is specified in the command line. If you place an object file in the models folder you would enter this in the command line: ./PA9

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Assimp and libmagick++ use this sudo  
On Ubuntu: 
```bash apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw-dev```

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2
```

## Building and Running
To run this project you need to use cmake which makes including new libraries easier, and handles new files added automatically to the src and include directory. Cmake is a small new learning curve but makes things easier in the future.

### CMake instructions
The makefile works as expected and must be updated with new files added in.
```bash
mkdir build
cd build
cmake ..
make
./PA9 
```

### Controls:
- 'p': switch between vertex and fragment lighting.  
- 'w': move cube up
- 's': move cube down
- 'a': move cube left
- 'd': move cube right
- 'space bar': apply force to the sphere.


## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./PA9
```
