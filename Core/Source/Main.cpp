//Standard Windows Crap
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>

//External Shit
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Custom Shit
#include "../include/cpu/chip8.hpp"
#include "../include/display/display.hpp"

void drawGraphics(GLFWwindow* window, chip8 processor)
{
	glClear(GL_COLOR_BUFFER_BIT);



	int modifier = 1;


	//Increment through Processor graphics array
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 64; x++)
		{

			if (processor.graphics[(y * 64) + x] == 0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			else
			{
				glColor3f(1.0f, 0.0f, 1.0f);
			}

		}
	}

	glBegin(GL_QUADS);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(1.0f, 1.0f);
	glEnd();

	//glPopMatrix();
	//glFlush();

	glfwSwapBuffers(window);

}

GLFWwindow* setupGraphics()
{
	std::cout << "GLFW Initializing" << std::endl;

	GLFWwindow* window;

	//Initializa the Library
	if (!glfwInit())
	{
		std::cout << "GLFW Initialization Failed" << std::endl;
		return NULL;
	}

	//Window Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(640, 320, "EmuC8", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW Window Failure" << std::endl;
		glfwTerminate();
		return NULL;
	}

	//Make the window's context current
	glewExperimental = GL_TRUE;
	glfwMakeContextCurrent(window);

	//Starting GLEW Extension Handler
	glewInit();

	// Get info of GPU and supported OpenGL version
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version Supported: " << glGetString(GL_VERSION) << std::endl;

	//Fix Aspect Ratio
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(120, 320.0f / 640.0f, 0.01f, 100.0f);

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
		{
			processor.emulateCycle();
		}


		//drawGraphics(window);
		if (processor.drawFlag)
		{
			drawGraphics(window, processor);
			processor.drawFlag = false;

			//processor.debugRender();
		}

		processor.setKeys();

		//Base GLFW Stuff to keep the window happy till I get shit working. 
		glfwPollEvents();
	}

	//Close out everything and call it successful
	glfwTerminate();
	return EXIT_SUCCESS;
}

