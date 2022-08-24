#pragma once

// Standard Libs
#include <string>
#include <memory>

// External Libs
#include "GLFW/glfw3.h"

// Custom Stuff
#include "audio/audio.hpp"

class cpu {
	private:
    
		void clearDisplay();
		void advanceProgram();

	public:

        // Constructor
        cpu();

        // Destructor
        ~cpu();

		bool halted; //Debug Use Only

		//Chip 8 OP Codes
		unsigned short opcode;

		//Chip 8 4K Memory
		unsigned char memory[4096];

		//Chip 8's 16 Registers
		unsigned char registers[16];

		//Index Register & Program Counter
		unsigned short index;
		unsigned short programCounter;

		//Chip 8 Video Graphics
		unsigned char graphics[64 * 32];

		//Chip 8 Timer Registers
		unsigned char delayTimer;
		unsigned char soundTimer;

		//stack & stack pointer
		unsigned short stack[16];
		unsigned short stackPosition;

		//Keypad Input
		unsigned char key[16];

		bool drawFlag; 

        // Buzzer Hardware
        std::unique_ptr<Buzzer> Sound;

		//Functions
        static void KeyInput(GLFWwindow* window, int key, int scancode, int action, int mode, void *parameter);

		void initialize();
		bool loadGame(const std::string& game);
		void emulateCycle();
};