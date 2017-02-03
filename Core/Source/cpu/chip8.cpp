//Standard Shit
#include <string>
#include <iostream>

//Custom Shit
#include "../../Include/cpu/chip8.hpp"

/*
0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
0x200-0xFFF - Program ROM and work RAM
*/

void chip8::initialize()
{
	programCounter = 0x200;
	opcode = 0;
	index = 0;

	// Clear Display
	// Clear Stack
	// Clear Registers V0 - VF
	// Clear Memory

	// Load Fontset
	for (int i = 0; i < 80; ++i)
	{ 
		//memory[i] = chip8_fontset[i];
	}

	//Reset Timers

}

void chip8::emulateCycle()
{
	// Fetch opcode
	opcode = memory[programCounter] << 8 | memory[programCounter + 1];

	//Decode Opcodes
	switch (opcode & 0Xf000)
	{
		default:
			std::cout << "Unknown Opcode: 0x%X\n", opcode; 
	}

	//Update Timers
	if (delayTimer > 0)
	{
		--delayTimer;
	}

	if (soundTimer > 0)
	{
		if (soundTimer == 1)
		{
			//Play Sounder
		}

		--soundTimer;
	}

}

void chip8::setKeys()
{
    //do nothing
}

void chip8::loadGame(std::string game)
{

}

