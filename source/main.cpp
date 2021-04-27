//Standard Crap
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
	if (!processor.loadGame("PONG.C8"))
    {
        glfwTerminate();
        std::cout << "TERMINATING EMULATOR" << std::endl;
        return EXIT_FAILURE;
    }

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

