/*#include <GLFW/glfw3.h>

int main ()
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
*/


//Standard Windows Crap
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>

//External Shit
#include "display/glad.h"
#include <GLFW/glfw3.h>

//Custom Shit
#include "cpu/chip8.hpp"
#include "display/display.hpp"


void setupInput()
{

}

int main()
{
	//Cute little baby processor
	chip8 processor;
	display window;

	//Setup Input Keys
	setupInput();

	//Initialize Shit
	processor.initialize();
	window.initialize();

	//We're just going to hard code pong for now
	processor.loadGame("PONG");

	//emulation loop
	
	while (!window.shouldClose())
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
			window.drawGraphics(processor);
			processor.drawFlag = false;

			//processor.debugRender();
		}

		//Do Something?
		processor.setKeys();

		//Base GLFW Stuff to keep the window happy till I get shit working. 
		glfwPollEvents();
	}

	//Close out everything and call it successful
	glfwTerminate();
	return EXIT_SUCCESS;
}

