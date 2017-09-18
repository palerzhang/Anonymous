#include <iostream>

#include "AsWindow.h"

// The MAIN function, from here we start the application and run the game loop
int main()
{
	AsWindow window(50,50,800,600, "Test Window");

	window.exec();

	return 0;
}