#include "hzpch.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {

	//*
	


	GLFWwindow* window;

	//* Initialize the library 
	if (!glfwInit())
		return -1;

	//* Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(1280, 960, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//* Make the window's context current 
	glfwMakeContextCurrent(window);

	// load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1280, 960);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});

	// triangle normalized verticies
	float vertices[] = {
	-0.1f,  0.5f, 0.0f,  // top right
	-0.1f, -0.5f, 0.0f,  // bottom right
	-0.9f, -0.5f, 0.0f,  // bottom left
	-0.9f,  0.5f, 0.0f,   // top left 
	 0.9f,  0.5f, 0.0f,  // top right
	 0.9f, -0.5f, 0.0f,  // bottom right
	 0.1f, -0.5f, 0.0f,  // bottom left
	 0.1f,  0.5f, 0.0f   // top left 
	};

	uint32_t indicies[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3,    // second triangle
	4, 5, 7,   // first triangle
	5, 6, 7    // second triangle
	};

	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	uint32_t ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);




	std::string vertexShaderS = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	void main()
	{
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
	)";

	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderC = vertexShaderS.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderC, NULL);
	glCompileShader(vertexShader);


	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	std::string fragmentShaderS = R"(
	#version 330 core
	out vec4 FragColor;
	uniform vec4 ourColor;
	
	void main()
	{
	    FragColor = ourColor;
	} 
	)";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderC = fragmentShaderS.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderC, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	uint32_t shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	

	//* Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//* Render here 
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeVal = glfwGetTime();
		float greenValue = (sin(timeVal) / 2.0f) + 0.5f;
		glUseProgram(shaderProgram);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(, 3, GL_TRIANGLES, vertices);
		glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(float), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_STATIC_DRAW, )

		//* Swap front and back buffers 
		glfwSwapBuffers(window);

		//* Poll for and process events 
		glfwPollEvents();

	}

	glfwTerminate();
	
	system("pause");
	//*/
	//return 0;
}