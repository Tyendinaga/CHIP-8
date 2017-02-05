//Standard Shit
#include <string>
#include <iostream>

//Custom Shit
#include "../../Include/cpu/chip8.hpp"

/*
Memory Map

0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
0x200-0xFFF - Program ROM and work RAM
*/

void chip8::initialize()
{
	programCounter = 0x200;
	opcode = 1;
	index = 0;

	// Clear Display
	// Clear Stack
	// Clear Registers V0 - VF
	// Clear Memory

	//This is the Fontset. 
	unsigned char fontset[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};


	// Load Fontset into Memory.
	for (int i = 0; i < 80; ++i)
	{ 
		memory[i] = fontset[i];
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
		//IMPLEMENT ALL OF THE FUCKING OP CODES. SOMEDAY. EVENTUALLY.

		//Op Code List
		
		//NNN: address
		//NN: 8-bit constant
		//N: 4-bit constant
		//X and Y: 4-bit register identifier

		//Have to Filter for the following op code patterns accordingly. Will probably use a switch statement. 

		//Holy Fuck this will be a lot of switches. 
		
		//0NNN
		//00E0
		//00EE
		//1NNN
		//2NNN
		//3XNN
		//4XNN
		//5XY0
		//6XNN
		//7XNN
		//8XY0
		//8XY1
		//8XY2
		//8XY3
		//8XY4
		//8XY5
		//8XY6
		//8XY7
		//8XYE
		//9XY0
		//ANNN
		//BNNN
		//CXNN
		//DXYN
		//EX9E
		//EXA1
		//FX07
		//FX0A
		//FX15
		//FX18
		//FX1E
		//FX29
		//FX33
		//FX55
		//FX65

		default:
			std::cout << "Unknown Opcode: 0x" << std::hex << opcode << std::endl;
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
			//Play Sound
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
	//We'll load it. Eventually.
	//Else I wont be able to bug opcodes. 
}

