#pragma once

// Standard Libs
#include <string>

// External Libs
#include <GLFW/glfw3.h>

// Custom Stuff
#include "../audio/audio.hpp"

class chip8 {
	private:
    
		void clearDisplay();
		void advanceProgram();

	public:

        chip8();

        ~chip8();

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
        Buzzer sound;

		//Functions
		void initialize();
		bool loadGame(const std::string& game);
		void emulateCycle();
};