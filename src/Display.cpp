#include "Display.hpp"

#include "gLErrorHandle.hpp"

const double Display::UPDATES_PER_SEC = 60.0;
const double Display::TARGET_DELTA_TIME = 1000000.0 / Display::UPDATES_PER_SEC;

Display::Display(unsigned int pWidth, unsigned int pHeight, const char* pTitle) : mWidth(pWidth), mHeight(pHeight), mTitle(pTitle), mWindow(glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL))
{
	scene = nullptr;
	input = new InputHandler(mWindow);
}

Display::~Display()
{
	if (scene != nullptr)
	{
		delete scene;
		scene = nullptr;
	}
	input->Unbind();
	
	// GLFW Termination
	glfwTerminate();
}

void Display::Initialize()
{
	GLCall(glViewport(0, 0, mWidth, mHeight));
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
	
	input->Bind();
	input->AddCommand(GLFW_KEY_ESCAPE, RELEASED, GLFW_MOD_NONE, [=](){ glfwSetWindowShouldClose(mWindow, true); });
	scene = new Scene(input);
}

void Display::RequestFocus()
{
	glfwMakeContextCurrent(mWindow);
}

void Display::Run()
{
	scene->Initialize((float) mWidth / (float) mHeight);
	
	glEnable(GL_DEPTH_TEST);
	
	// Render loop
	double deltaTime = 0.0;
	timer.start();
	while (!glfwWindowShouldClose(mWindow))
	{
		GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		
		// Fixed Update (as opposed to a deltaTime update)
		// getElapsedTime...() automatically stops the timer so timer.stop() is not needed
		deltaTime += timer.getElapsedTimeInMicroSec(); // Cumulative
		if (deltaTime >= TARGET_DELTA_TIME)
		{
			deltaTime -= TARGET_DELTA_TIME;
			scene->Update();
		}
		timer.start();
		
		scene->Render();
		
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
	timer.stop();
}

void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}