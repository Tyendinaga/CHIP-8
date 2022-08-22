#include "emulator.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

// External Libraries
#include "display/glad.h"
#include "GLFW/glfw3.h"

// Custom Libraries
#include "cpu/cpu.hpp"
#include "display/display.hpp"

emulator::emulator() = default;

void emulator::Boot() {

    //Cute little baby processor
    std::unique_ptr<cpu> processor(new cpu());
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
    glfwSetKeyCallback(window.GetWindow(), reinterpret_cast<GLFWkeyfun>(cpu::KeyInput));

	//We're just going to hard code pong for now
	if (!processor->loadGame("PONG.C8"))
    {
        glfwTerminate();
        std::cout << "TERMINATING EMULATOR" << std::endl;
        return;
    }

	//emulation loop
	while (!window.shouldClose())
	{
		// Sleep for 16 Milliseconds between cycles
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

        if (!paused) {

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
        }


		//Base GLFW Stuff to keep the window happy till I get shit working.
		glfwPollEvents();
	}

	//Close out everything and call it successful
	glfwTerminate();

}

void emulator::Play() {
    paused = false;
}

void emulator::Pause() {
    paused = true;
}
