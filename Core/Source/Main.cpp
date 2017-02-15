//Standard Windows Crap
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>

//External Shit
#include <GL\glew.h>
#include <GLFW\glfw3.h>

//Custom Shit
#include "../Include/cpu/chip8.hpp"

void drawGraphics(GLFWwindow* window)
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

GLFWwindow* setupGraphics()
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

void setupInput()
{

}

int main()
{
	//Cute little baby processor
	chip8 processor;

	//Initialize the GLFW Library
	GLFWwindow* window = setupGraphics();
	
	if (window == NULL)
	{
		return EXIT_FAILURE;
	}


	setupInput();
	processor.initialize();

	//We're just going to hard code pong for now
	processor.loadGame("PONG");

	//emulation loop
	while (!glfwWindowShouldClose(window))
	{
		//Slowing down the cycle rate a bit. 
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		if (!processor.halted)
			processor.emulateCycle();

		//drawGraphics(window);
		if (processor.drawFlag)
		{
			drawGraphics(window);
			processor.drawFlag = false;
		}

		processor.setKeys();

		//Base GLFW Stuff to keep the window happy till I get shit working. 
		glfwPollEvents();

	}

	//Close out everything and call it successful
	glfwTerminate();
	return EXIT_SUCCESS;
}

