#This is Anonymous. 

Welcome :)

GLEW and GLFW are required

OpenGL is required over version 3.0

Please use VS2013(VC12).

#Setup the project

1. Clone or download the repository.

2. Create a VS2013 project in the directory where you put the repository.

3. Add the source code (.h .cpp) into your project.

4. Configure the library path

5. Configure the library that you need to use. Choose static or dynamic library:

For adopting static library:
- Using GLEW_STATIC in code
- Using glew32s.lib, glfw3.lib, opengl32.lib

For adopting dynamic library:
- No GLEW_STATIC in code
- Using glew32.lib, glfw3dll.lib, opengl32.lib