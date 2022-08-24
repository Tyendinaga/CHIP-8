//Standard Windows Crap
#include <iostream>
#include <vector>

//External Shit
#include "glad.h"
#include "GLFW/glfw3.h"

//Custom Shit
#include "display.hpp"

bool display::initialize()
{

    ///////////////////
    // CREATE WINDOW //
    ///////////////////
	std::cout << "GLFW Initializing" << std::endl;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "GLFW Initialization Failed" << std::endl;
		return false;
	}

	//Window Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Don't resize the window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create a 640 by 320 Window to play the game in.
	window = glfwCreateWindow(640, 320, "CHIP-8", nullptr, nullptr);
	if (!window)
	{
		std::cout << "GLFW Window Failure" << std::endl;
		glfwTerminate();
		return false;
	}

	//Set Context (Must be before GLAD)
	glfwMakeContextCurrent(window);

	//Set Resize Function
	glfwSetFramebufferSizeCallback(window, display::framebufferSizeCallback);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

    ////////////////////////
    // SHADER COMPILATION //
    ////////////////////////

	//SHADER COMPILATION VARIABLES
	//----------------------------
	int compiled;
	char compileLog[512];

	//SHADER SOURCE CODE
	//------------------
	const GLchar *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

    const GLchar *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";

	//COMPILE VERTEX SHADER
	//---------------------
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//CHECK SHADER COMPILATION
	//------------------------
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, compileLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << compileLog << std::endl;
	}

	//COMPILE FRAGMENT SHADER
	//-----------------------
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	//CHECK SHADER COMPILATION
	//------------------------
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, compileLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << compileLog << std::endl;
	}

	//LINK SHADER PROGRAM
	//-------------------
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//CHECK SHADER LINKAGE
	//--------------------
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compiled);
	if (!compiled) 
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, compileLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << compileLog << std::endl;
	}

	//CLEANUP SHADER ARTIFACTS
	//------------------------
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    //USE THE SHADER PROGRAM
    //-----------------
    glUseProgram(shaderProgram);

    // SET CLEAR COLOUR
    //-----------------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

//Draw Game Shit
void display::drawGraphics(cpu* processor)
{
	//VAO Storage
	std::vector<unsigned int> VAOa;
	std::vector<unsigned int>::iterator VAOi;

    //VBO Storage
    std::vector<unsigned int> VBOa;
    std::vector<unsigned int>::iterator VBOi;

	//Iterate Through Rows
	for (int y = 0; y < 32; ++y)
	{
		//Iterate Through Columns
		for (int x = 0; x < 64; ++x)
		{
			if (processor->graphics[(y * 64) + x] == 0)
			{

			}
			else
			{
				//Offsets
				float yOffset = 0.0625f;
				float xOffset = 0.03125f;

				//Offset Pixel
				std::vector<float> vertices1 = {
					-1.0f + (xOffset * x), 0.9375f - (yOffset * y), 0.0f, // Bottom Left Corner

					-0.96875f + (xOffset * x), 1.0f - (yOffset * y), 0.0f, // Top right 

					-1.0f + (xOffset * x),  1.0f - (yOffset * y), 0.0f  // Top Left Corner
				};

				std::vector<float> vertices2 = {
					-1.0f + (xOffset * x) , 0.9375f - (yOffset * y), 0.0f, // Bottom Left Corner

					-0.96875f + (xOffset * x), 1.0f - (yOffset * y), 0.0f,  // Top right 

					-0.96875f + (xOffset * x), 0.9375f - (yOffset * y), 0.0f  // Bottom Right Corner
				};

				//Add 'Pixel'
				generate(vertices1, VAOa, VBOa);
				generate(vertices2, VAOa, VBOa);
			}
		}
	}

	//RENDER BACKGROUND COLOUR
	//------------------------
	glClear(GL_COLOR_BUFFER_BIT);

    //DRAW OUR TRIANGLE
    //-----------------
	//Iterate through VAO Vector
	for (VAOi = VAOa.begin(); VAOi < VAOa.end(); VAOi++)
	{
		glBindVertexArray(*VAOi);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glfwSwapBuffers(window);

	//Iterate through VAO Vector
	for (VAOi = VAOa.begin(); VAOi < VAOa.end(); VAOi++)
	{
		glDeleteVertexArrays(1, &*VAOi);
	}

    //Iterate through VBO Vector
    for (VBOi = VBOa.begin(); VBOi < VBOa.end(); VBOi++)
    {
        glDeleteBuffers(1, &*VBOi);
    }
}

void display::generate(std::vector<float> vertices, std::vector<unsigned int> &VAOa, std::vector<unsigned int> &VBOa) {

    unsigned int VAO;
    unsigned int VBO;

    //Get Size of Vertices Vector in Bytes
    GLsizei size = vertices.size() * sizeof(vertices[0]);

    //GENERATE ARRAYS AND BUFFERS
    //---------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //BINDING
    //-------
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], GL_STATIC_DRAW);

    //BIND VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //Do not Work with Vertex Array
    glBindVertexArray(0);

    //Do not work with Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Save Data
    VAOa.push_back(VAO);
    VBOa.push_back(VBO);
}

bool display::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void display::framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
	std::cout << "Frame Buffer Updated" << std::endl;
	glViewport(0, 0, width, height);
}

GLFWwindow* display::GetWindow()
{
    return window;
}




