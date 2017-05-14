//Standard Windows Crap
#include <iostream>

//External Shit
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Custom Shit
#include "../../Include/display/display.hpp"

//Constructor
display::display()
{

}

//Setup OpenGL Context
GLFWwindow* display::setupGraphics()
{
	std::cout << "GLFW Initializing" << std::endl;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "GLFW Initialization Failed" << std::endl;
		return NULL;
	}

	window = glfwCreateWindow(640, 320, "EmuC80", NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW Window Failure" << std::endl;
		glfwTerminate();
		return NULL;
	}

	//Make the window's context current
	glewExperimental = GL_TRUE;
	glfwMakeContextCurrent(window);

	//Starting GLEW Extension Handler
	glewInit();

	// Get info of GPU and supported OpenGL version
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version Supported: " << glGetString(GL_VERSION) << std::endl;

	//Draw once to Make things Nice
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	return window;
}


//Draw Game Shit
void display::drawGraphics(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Testing Stuff
	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	//Magic OpenGL Nonsense I don't remotely understand. 
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	//Shit I understand even less
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Magical Shader Bullshit
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	//The Magic
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//End Testing


	glfwSwapBuffers(window);
}
