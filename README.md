#This is Anonymous. 

Welcome :)

OpenGL is required over version 4.0

With: GLFW(3.2.1), GLAD(build in gl 4.0), stb image loader

Please use VS2013(VC12).

#Setup the project

1. Clone or download the repository.

2. Create a VS2013 project in the directory where you put the repository.

3. Add the source code (.h .cpp) into your project.

4. Configure the library path

5. Configure the library that you need to use. Choose static or dynamic library:

For adopting static library:
- Using glfw3.lib, opengl32.lib

For adopting dynamic library:
- Using glfw3dll.lib, opengl32.lib

*Addition
GLAD configuration: https://learnopengl-cn.github.io/01%20Getting%20started/02%20Creating%20a%20window/#glad
STB image: https://github.com/nothings/stb/blob/master/stb_image.h
How to use STB: https://learnopengl-cn.github.io/01%20Getting%20started/06%20Textures/#stb_imageh
