//Standard Crap
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>
#include <memory>

//External Shit
#include "display/glad.h"
#include <GLFW/glfw3.h>

//Custom Shit
#include "cpu/chip8.hpp"
#include "display/display.hpp"

int main()
{
	//Cute little baby processor
    std::unique_ptr<chip8> processor(new chip8());
	display window;

	//Initialize Shit
	processor->initialize();
	window.initialize();

    /**
     * Set User Pointer
     *
     * Setting the user pointer lets us retrieve this value later.
     */
    glfwSetWindowUserPointer(window.GetWindow(), processor.get());

    /**
     * Set Callback Keys
     */
    glfwSetKeyCallback(window.GetWindow(), reinterpret_cast<GLFWkeyfun>(chip8::KeyInput));



	//We're just going to hard code pong for now
	if (!processor->loadGame("HELLO.C8"))
    {
        glfwTerminate();
        std::cout << "TERMINATING EMULATOR" << std::endl;
        return EXIT_FAILURE;
    }

	//emulation loop
	while (!window.shouldClose())
	{
		// Sleep for 16 Milliseconds between cycles
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

        //
		if (!processor->halted)
		{
			processor->emulateCycle();
		}

        //
		if (processor->drawFlag)
		{
			window.drawGraphics(processor.get());
			processor->drawFlag = false;
		}

		//Base GLFW Stuff to keep the window happy till I get shit working. 
		glfwPollEvents();
	}

	//Close out everything and call it successful
	glfwTerminate();
	return EXIT_SUCCESS;
}

