# PA11: Pool Game 

## Team Members
- Brett Knadle  
- Phillip Vong  
- Randy Gonzalez  

## Objective:
- To build an interactive Pool Game.
- Use Assimp to load models and textures.
- Use Bullet to handle the physics.

# Assignment:
- Building an interactive Pool Game with models and textures loading. Use Bullet library to handle the physics of the game.

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Assimp and libmagick++
```bash
sudo apt-get install g++ freeglut3-dev glew1.5-dev libmagick++-dev libassimp-dev libglfw-dev
```

### Glew, GLM, SDL2
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```
### Bullet Libray
```bash
sudo apt-get install libbullet-dev
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
./Pool
```

### Controls:
	Controls:
	- left arrow------------ 	Move Pool Stick to Left
	- right arrow ---------- 	Move Pool Stick to Right
	- space-----------------	hit the ball 
	- o-----------------------	Restart Game

	Views:
	- u -----------------	reset view
	- q------------------	increment X value on camera
	- w-----------------	increment Y value on camera
	- e------------------	Increment Z value on camera
	- r-----------------    Decrement X value on camera 
	- t------------------	Decrement Y value on camera
	- y------------------	Decrement Z value on camera

	Lighting:
	- f--------------- 	Increment specular Light
	- d--------------- 	Decrement specular Light  
	- s --------------	Increment Ambient Light 
	- a---------------	Decrement Ambient Light
	- p---------------	Switch between Shader Lighting


## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Pool
```
