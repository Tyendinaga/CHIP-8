#ifndef DISPLAY_HPP
#define DISPLAY_HPP


//External Shit
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class display {
private:

	//OpenGL Context
	GLFWwindow* window;

public:

	//Construction
	display();

	//Functions
	GLFWwindow * setupGraphics();
	void drawGraphics(GLFWwindow* window);
	
};

#endif /* DISPLAY_HPP */