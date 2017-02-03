#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <string>

class chip8 {
    //private:
    
    public:

	   chip8();

       bool drawFlag; 
       
	   void initialize();
	   void loadGame(std::string game);
       void emulateCycle(); 
       void setKeys();
        
};


#endif /* CHIP8_HPP */

