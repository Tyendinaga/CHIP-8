#ifndef DISPLAY_HPP
#define DISPLAY_HPP


//External Shit
#include "glad.h"
#include <GLFW/glfw3.h>
#include "../cpu/chip8.hpp"
#include <vector>

class display {
private:

	//OpenGL Context
	GLFWwindow* window;

	//Shader Program
	int shaderProgram;

	//Thingers
	unsigned int VBO;
	unsigned int VAO;
	unsigned int VAO2;

public:

	//Functions
	bool initialize();
	void drawGraphics(chip8 processor);
	bool shouldClose();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	
	unsigned int generate(std::vector<float> vertices);
	
};

#endif /* DISPLAY_HPP */