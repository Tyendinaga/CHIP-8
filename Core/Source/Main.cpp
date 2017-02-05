//Standard Windows Crap
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>

//External Shit
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Custom Shit
#include "../Include/cpu/chip8.hpp"

void drawGraphics(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
}

GLFWwindow* setupGraphics()
{
	std::cout << "GLFW Initializing" << std::endl;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{ 
		std::cout << "GLFW Initialization Failed" << std::endl;
		return NULL;
	}

	window = glfwCreateWindow(640, 320, "EmuC80", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW Window Failure" << std::endl;
		glfwTerminate();
		return NULL;
	}

	//Make the window's context current 
	glfwMakeContextCurrent(window);

	//Starting GLEW Extension Handler
	glewInit();

	// Get info of GPU and supported OpenGL version
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version Supported: " << glGetString(GL_VERSION) << std::endl;

	//Draw once to Make things Nice
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

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
		return EXIT_FAILURE;
	}


	setupInput();
	processor.initialize();

	//We're just going to hard code pong for now
	processor.loadGame("PONG");

	//emulation loop
	while (!glfwWindowShouldClose(window))
	{
		//Slowing down the cycle rate a bit. 
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		if (!processor.halted)
			processor.emulateCycle();

		drawGraphics(window);
		if (processor.drawFlag)
		{
		//	drawGraphics(window);
		}

		processor.setKeys();

		//Base GLFW Stuff to keep the window happy till I get shit working. 
		glfwPollEvents();

	}

	return EXIT_SUCCESS;
}

