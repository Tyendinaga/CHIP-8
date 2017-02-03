/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chip8.hpp
 * Author: Peter Rose
 *
 * Created on February 2, 2017, 7:30 PM
 */



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

