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
	//unsigned int VBO;
	//unsigned int VAO;

public:

    //
    GLFWwindow* GetWindow();

	//Functions
	bool initialize();
	void drawGraphics(chip8* processor);
	bool shouldClose();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    // Vars
	void generate(std::vector<float> vertices, std::vector<unsigned int>& VAOa, std::vector<unsigned int>& VBOa);
	
};

#endif /* DISPLAY_HPP */