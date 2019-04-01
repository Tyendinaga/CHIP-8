//Standard Shit
#include <string>
#include <iostream>
#include <fstream>

//Custom Shit
#include "chip8.hpp"

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

	//Debug Flag
	halted = false;

	// Clear Display
	clearDisplay();
	
	//Clear Stack
	stackPosition = 0;
	for (int i = 0; i < 15; i++)
	{
		stack[i] = 0;
	}

	// Clear Registers V0 - VF


	// Clear Memory
	for (int i = 0; i < 2048; i++)
	{
		memory[i] = 0;
	}


	//This is the Fontset. 
	//It might look like random garbage but if you compare it to its binary
	//Representation you'll see that they 'Look' like the numbers when aligned. 
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

void chip8::clearDisplay() {
	for (int i = 0; i < 2048; i++)
	{
		graphics[i] = 0;
	}
}

void chip8::emulateCycle()
{
	// Fetch opcode
	opcode = memory[programCounter] << 8 | memory[programCounter + 1];

	/* 
		Identifying OP Codes

		So We take the OPCode and essentially apply a filter. 
		Let's say we have an OPCode, Imma pull one out of my ass. 

		0x370C

		We can't make a switch with every possible op code built in so we need to filter based on their indvidual characteristics. 

		if you 0x370C & 0xF000 you get a result of 0x3000. This allows us to break down the opcodes to a level where we can identify
		The parts that identify specific operations the code itself is meant to perform, after which we can perform the actual logic with them. 
	*/

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

		//Case SubSwitch
		case 0x000: //A Bunch of codes match this pattern So we need to do more switching. 
		{
			switch (opcode & 0x00F)
			{

				//Not Emulated 0NNN For Reasons

				//00E0 (Clear Screen)
				case 0x0000: 
				{
					clearDisplay();
					advanceProgram();
					drawFlag = true;
					break;
				}

				//00EE (Return from SubRoutine)
				case 0x000E: 
				{
					//Return back to the previous stack position and set program counter to the stored address
					stackPosition--;
					programCounter = stack[stackPosition];
					advanceProgram();
					break;
				}

				//Shits fucked up.
				default:
				{
					std::cout << "Unknown Opcode: 0x" << std::hex << opcode << std::endl;
					halted = true;
				}

			}

			break;
		}


		//1NNN Jumps to Addres NNN
		case 0x1000:
		{
			programCounter = (opcode & 0x0FFF);
			break;
		}

		//2NNN Calls Subroutine at NNN
		case 0x2000:
		{
			//Set the current program counter to the stack position and increment
			stack[stackPosition] = programCounter;
			stackPosition++;

			//Set Program Counter to the Subroutine
			programCounter = (opcode & 0x0FFF);
			break;
		}

		//3XNN (Jumps an extra instruction if Register X is equal to NN)
		case 0x3000:
		{
			if (registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			{
				advanceProgram();
			}

			advanceProgram();
			break;
		}

		//4XNN Jumps an extra instruction if Register X doesn't equal NN
		case 0x4000:
		{
			if (registers[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
			{
				advanceProgram();
			}

			advanceProgram();
			break;
		}

		//5XY0 Jumps an instruction if Register X is equal to Register Y
		case 0x5000:
		{
			if (registers[(opcode & 0x0F00) >> 8] == registers[(opcode & 0x00F0) >> 4]
			{
				advanceProgram();
			}

			advanceProgram();
			break;
		}


		//6XNN (Sets Regiser X to value of NN)
		case 0x6000:
		{
			registers[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
			advanceProgram();
			break;
		}

		//7XNN (Adds value of NN to register X)
		case 0x7000:
		{
			registers[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
			advanceProgram();
			break;
		}

		//8XY0 Through 8XYE
		case 0x8000:
		{
			switch (opcode & 0x000f)
			{
				//8XY0 Set X to Y
				case 0x0000:
				{
					registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x0F00) >> 8];
					advanceProgram();
					break;
				}

				//8XY1 Set X to X OR Y
				case 0x0001:
				{
					registers[(opcode & 0x0F00) > 8] = registers[(opcode & 0x0F00) >> 8] | registers[(opcode & 0x0F00) >> 8];
					advanceProgram();
					break;
				}

				//8XY2 Set X to X AND Y
				case 0x0002:
				{
					registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x0F00) >> 8] & registers[(opcode & 0x00F0) >> 4];
					advanceProgram();
					break;
				}

				//8XY3 Set X to X XOR Y
				case 0x0003:
				{
					registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x0F00) >> 8] ^ registers[(opcode & 0x00F0) >> 4];
					advanceProgram();
					break;
				}
				//8XY4 X = X + Y
				case 0x0004:
				{
					if (registers[(opcode & 0x00F0) >> 4] > (0xFF - registers[(opcode & 0x0F00) >> 8]))
					{
						registers[0xF] = 1; //carry
					}
					else 
					{
						registers[0xF] = 0;
					}
						
					registers[(opcode & 0x0F00) >> 8] += registers[(opcode & 0x00F0) >> 4];

					advanceProgram();
					break;
				}
				//8XY5 X = X - Y;
				case 0x0005:
				{
					if (registers[(opcode & 0x00F0) >> 4] > registers[(opcode & 0x0F00) >> 8])
					{
						registers[0xF] = 0; // Borrow
					}
					else
					{
						registers[0xF] = 1;
					}
						
					registers[(opcode & 0x0F00) >> 8] -= registers[(opcode & 0x00F0) >> 4];

					advanceProgram();
					break;
				}
				//8XY6
				case 0x0006:
				{
					halted = true;
					break;
				}
				//8XY7
				case 0x0007:
				{
					if (registers[(opcode & 0x0F00) >> 8] > registers[(opcode & 0x00F0) >> 4]) 
					{
						registers[0xF] = 0; // Borrowed
					}
					else
					{
						registers[0xF] = 1; //Not Borrowed
					}
						
					registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x00F0) >> 4] - registers[(opcode & 0x0F00) >> 8];

					advanceProgram();
					break;
				}
				//8XYE
				case 0x000E:
				{
					halted = true;
					break;
				}

			}
			break;
		}

		//9XY0
		case 0x9000:
		{
			halted = true;
			break;
		}

		//ANNN Sets Index to NNN 
		case 0xA000:
		{
			index = (opcode & 0x0FFF);
			advanceProgram();
			break;
		}

		//BNNN
		case 0xB000:
		{
			halted = true;
			break;
		}

		//CXNN
		case 0xC000:
		{
			registers[(opcode & 0x0F00) >> 8] = rand() & (opcode & 0x00FF);
			advanceProgram();
			break;
		}

		//DXYN Draws a sprite at the coordinate Register X and Register Y with a width of 8 and a height of N
		case 0xD000:
		{
			//Extract X, Y, and Height
			unsigned short x = registers[(opcode & 0x0F00) >> 8];
			unsigned short y = registers[(opcode & 0x00F0) >> 4];
			unsigned short height = opcode & 0x000F;
			unsigned short pixel;
			
			//Register F is set to 1 in the event that drawing a sprite causes pixels to be flipped off. 
			registers[0xF] = 0;

			for (int yline = 0; yline < height; yline++)
			{
				//The specification for this opcode notes that the index is used as a starting point for drawing the pixels
				pixel = memory[index + yline];

				//This is where we specify how wide the sprite is. 
				for (int xline = 0; xline < 8; xline++)
				{
					if ((pixel & (0x80 >> xline)) != 0)
					{
						//Not a hundred percent sure how exactly this math works
						if (graphics[(x + xline + ((y + yline) * 64))] == 1)
						{
							registers[0xF] = 1;
						}

						graphics[x + xline + ((y + yline) * 64)] ^= 1;
					}
				}
			}

			drawFlag = true;
			advanceProgram();
			break;
		}


		//EXNN
		case 0xE000:
		{
			switch (opcode & 0x00ff)
			{
				//EX9E skip instruction if KEY in VX is pressed.
				case 0x009E:
				{

					if (key[registers[(opcode & 0x0F00 >> 8)]] != 0)
					{
						advanceProgram();
					}

					advanceProgram();
					break;
				}

				//EXA1 Skip instruction if KEY in VX is not pressed.
				case 0x00A1:
				{

					if (key[registers[(opcode & 0x0F00 >> 8)]] == 0)
					{
						advanceProgram();
					}

					advanceProgram();
					break;
				}

				//Shits fucked up.
				default:
				{
					std::cout << "Unknown Opcode: 0x" << std::hex << opcode << std::endl;
					halted = true;
				}
			}

			break;
		}

		//FX07 THROUGH FX65
		case 0xf000:
		{
			switch (opcode & 0x00ff)
			{
				//FX07 Set Register X to Delay Timer
				case 0x0007:
				{
					registers[(opcode & 0x0F00) >> 8] = delayTimer;
					advanceProgram();
					break;
				}

				//FX0A
				case 0x000A:
				{
					halted = true;
					break;
				}

				//FX15, Set delay time to X
				case 0x0015:
				{
					delayTimer = (opcode & 0x0F00) >> 8;
					advanceProgram();
					break;
				}

				//FX18
				case 0x0018:
				{
					soundTimer = (opcode & 0x0F00) >> 8;
					advanceProgram();
					break;
				}

				//FX1E
				case 0x001E:
				{
					halted = true;
					break;
				}

				//FX29
				case 0x0029:
				{
					index = registers[(opcode & 0x0F00) >> 8];
					advanceProgram();
					break;
				}

				//FX33
				case 0x0033:
				{
					memory[index] = registers[(opcode & 0x0F00) >> 8] / 100;
					memory[index + 1] = (registers[(opcode & 0x0F00) >> 8] / 10 % 10);
					memory[index + 2] = (registers[(opcode & 0x0F00) >> 8] % 100) % 10;
					advanceProgram();
					break;
				}

				//FX55
				case 0x0055:
				{
					halted = true;
					break;
				}

				//FX65
				case 0x0065:
				{

					for (int i = 0; i < ((opcode & 0x0F00) >> 8); i++)
					{
						registers[i] = memory[index + i];
					}

					advanceProgram();
					break;
				}
			}

			break;
		}

		//Situation Normal, All fucked up. 
		default:
		{
			halted = true;
		}
	}

	
	if (!halted)
	{
		std::cout << "Processed Code: 0x" << std::hex << opcode << std::endl;
	}
	else
	{
		std::cout << "Unknown Opcode: 0x" << std::hex << opcode << std::endl;
		return;
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
			//TODO: Play Sound
		}

		--soundTimer;
	}
}

void chip8::setKeys()
{
    //do nothing
}
 
void chip8::advanceProgram() 
{
	programCounter += 2;
}

void chip8::loadGame(std::string progName)
{
	std::cout << "LOADING ROM: " << progName << std::endl;

	//Create Get the ROM from the file system. 
	std::ifstream rom;
	rom.open(progName, std::ios::in | std::ios::binary);

	//Check if ROM exists
	if (!rom)
	{
		std::cout << "EMULATION ERROR: " << progName << " NOT FOUND" << std::endl;
	}
	else
	{
		//ROMS for the chip 8 are loaded into a space of memory that ranges from about 
		//0x200 to 0xFFF, This gives us a total of 3583 Bytes.
		//I don't know how well it will work but I'll just grab the whole amount from file.
		char programBuffer[3583];
		rom.read(programBuffer, sizeof programBuffer);

		//Load ROM into Memory
		for (int i = 0; i < sizeof programBuffer; i++)
		{
			memory[i + 512] = programBuffer[i];
		}
	}

	rom.close();
}

