#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string>

class chip8 {
	private:
    
		void clearDisplay();
		void advanceProgram();

	public:
		//Variables. Will Probably have to make private


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
		
		//Functions
		void initialize();
		void loadGame(std::string game);
		void emulateCycle(); 
		void setKeys();
};


#endif /* CHIP8_HPP */

