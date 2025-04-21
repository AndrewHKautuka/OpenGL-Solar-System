#include "Display.hpp"

Display::Display(unsigned int pWidth, unsigned int pHeight, const char* pTitle) : mWidth(pWidth), mHeight(pHeight), mTitle(pTitle), mWindow(glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL))
{
	
}

Display::~Display()
{
	
}

void Display::Initialize()
{
	glViewport(0, 0, mWidth, mHeight);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
}

void Display::RequestFocus()
{
	glfwMakeContextCurrent(mWindow);
}

void Display::Run()
{
	// Render loop
	while (!glfwWindowShouldClose(mWindow))
	{
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
				
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
	
	// GLFW Termination
	glfwTerminate();
}

void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}