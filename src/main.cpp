#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Display.hpp"
#include "DisplayDataFileUtil.hpp"

int main()
{
	// GLFW Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	DisplayData* displayData = ReadDisplayDataFromFile("window.mod", mode);
	
	// Window Creation
	Display display(monitor, *displayData, "Solar System");
	
	delete displayData;
	displayData = nullptr;
	
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