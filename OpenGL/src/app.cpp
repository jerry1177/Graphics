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

	glViewport(0, 0, 800, 600);



	//* Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//* Render here 
		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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