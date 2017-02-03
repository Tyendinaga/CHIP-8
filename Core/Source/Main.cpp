//Standard Windows Crap
#include <cstdlib>

//External Shit
#include <GLFW\glfw3.h>

//Custom Shit
#include "../Include/cpu/chip8.hpp"

void drawGraphics()
{

}

GLFWwindow* setupGraphics()
{

	bool status = true;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{ 
		status = false;
	}

	window = glfwCreateWindow(640, 480, "EmuC80", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		status = false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	return window;
}

void setupInput()
{

}

int main()
{
	//Cute little baby processor
	chip8 processor;

	//Initialize the GLFW Library
	GLFWwindow* window = setupGraphics();
	
	if (window == NULL)
	{
		//return EXIT_FAILURE;
	}


	setupInput();
	processor.initialize();
	processor.loadGame("pong");

	//emulation loop
	while (!glfwWindowShouldClose(window))
	{
		processor.emulateCycle();


		if (processor.drawFlag)
		{
			drawGraphics();
		}

		processor.setKeys();


		//Base GLFW Stuff to keep the window happy till I get shit working. 
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	return EXIT_SUCCESS;
}

