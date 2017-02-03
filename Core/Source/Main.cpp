//Standard Windows Crap
#include <cstdlib>

//External Shit
#include <GLFW\glfw3.h>

//Custom Shit
#include "../Include/cpu/chip8.hpp"

//Chip 8 OP Codes
unsigned short opcode;

//Chip 8 memory
unsigned char memory[4096];

/*
0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
0x200-0xFFF - Program ROM and work RAM
*/

//Index and Program Counter
unsigned short index;
unsigned short programCounter;

//Registers
unsigned char Register[16];

//Chip 8 VGA Adapter
unsigned char gfx[64 * 32];

//Chip 8 Timer Registers
unsigned char delay_timer;
unsigned char sound_timer;

//stack
unsigned short stack[16];
unsigned short stackPosition;

//Keypad Input
unsigned char key[16];

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

