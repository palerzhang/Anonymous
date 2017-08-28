#include <iostream>

// GLEW
//#define GLEW_STATIC
#include "GLEW/glew.h"

// GLFW
//#include "GLFW/glfw3.h"

#include "AsWindow.h"

// The MAIN function, from here we start the application and run the game loop
int main()
{
	AsWindow window(50,50,400,400, "Test Window");

	window.exec();

	return 0;
}