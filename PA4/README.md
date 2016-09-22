#Randy Gonzalez
#CS 480- Graphics
#PA3 Compiling Instructions

To compile the program, make a new directory, name it build
cd build
Under the build directory type
cmake ..
Then type
make

To run executable, remain under build directory and type
./Tutorial
Program should execute accordingly.

#While running Executable
Press Following keys to interact with Cube

#Planet Key Inputs
'q' - Reverse orbit
'w' - Reverse Rotate
'e' - Pause Completely **also works as a reset key** #double tap triggers reset for all keys
'r' - Pause rotation
't' - Pause orbit

#Moon Key inputs
'a' - Reverse orbit
's' - Reverse rotate
'd' - Pause completely
'f' - pause rotation
'g' - pause orbit

**NOTE**
Avoid turning all keys on, may get confusing
Program works so that if the user presses q it will reverse orbit but at the same
time if the user enters w in succession it will keep the reversed orbit and also
reverse the rotation.
Program works well for multiple key inputs but it is best displayed if buttons are toggled.

**NOTE FOR MOON**
Moon interactions work as expected but best if seen if the planet model is paused.
Also best displayed if key is turned on then off before the next keyboard input.


#Shader files are under /PA3/shaders directory.
