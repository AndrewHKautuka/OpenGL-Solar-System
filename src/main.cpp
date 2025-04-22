#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Display.hpp"

const float WIDTH = 800, HEIGHT = 600;

int main()
{
	// GLFW Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Window Creation
	Display display(WIDTH, HEIGHT, "Solar System");
	
	if (display.mWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	display.RequestFocus();
	
	// GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	display.Initialize();
	display.Run();
	
	return 0;
}