# PA10: Pinball 

## Team Members
- Brett Knadle  
- Phillip Vong  
- Randy Gonzalez  

## Objective:
- To build an interactive Pinball Game.
- Use Assimp to load models and textures.
- Use Bullet to handle the physics.

# Assignment:
- Building an interactive Pinball Game with models and textures loading. Use Bullet library to handle the physics of the game.

## Dependencies, Building, and Running
This program only runs if a object file path is specified in the command line. If you place an object file in the models folder you would enter this in the command line: ./PA10

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

For Assimp and libmagick++ use this sudo  
On Ubuntu: 
```bash
apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw-dev
```

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
./PA10 
```

### Controls:
	- �z�---------- Left Paddle
	- �/� --------- Right Paddle
	- �space�----launch the ball (start the game)
	- �p�--------- Change per Vertex between Per Fragment Lighting
	- �t� --------- Side View
	- �y�--------- zoom out view
	- �r�--------- default view
	- �a�-------- decrement specular light
	- �d�-------- increment specular light  
	- �w�-------- decrement ambient light
	- �s� -------- increment ambient light 

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./PA10
```