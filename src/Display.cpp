#include "Display.hpp"

#include <iostream>
#include "gLErrorHandle.hpp"

const double Display::UPDATES_PER_SEC = 60.0;
const double Display::TARGET_DELTA_TIME = 1000000.0 / Display::UPDATES_PER_SEC;

Display::Display(DisplayData pData, const char* pTitle) : Display(NULL, data, pTitle)
{}

Display::Display(GLFWmonitor* pMonitor, DisplayData pData, const char* pTitle) : data(pData), monitor(pMonitor), mTitle(pTitle), mWindow(glfwCreateWindow(data.GetWidth(), data.GetHeight(), mTitle, data.IsFullscreen() ? pMonitor : NULL, NULL))
{
	scene = nullptr;
	input = new InputListener(mWindow);
	inputMapping = ReadInputMappingFromFile("controls.mod");
	
	data.SetOnFullscreenChange([&](){
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(mWindow, (data.IsFullscreen() ? monitor : NULL), (mode->width - data.GetWidth()) / 2, (mode->height - data.GetHeight()) / 2, data.GetWidth(), data.GetHeight(), mode->refreshRate);
	});
}

Display::~Display()
{
	if (scene != nullptr)
	{
		delete scene;
		scene = nullptr;
	}
	if (inputMapping != nullptr)
	{
		delete inputMapping;
		inputMapping = nullptr;
	}
	input->Unbind();
	
	// GLFW Termination
	glfwTerminate();
}

void Display::Initialize()
{
	GLCall(glViewport(0, 0, data.GetWidth(), data.GetHeight()));
	// Window is not resizable so the callback will (probably) never be invoked through here
	// but is left alone in case this interpretation is not correct
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
	
	input->SetInputMapping(inputMapping);
	input->Bind();
	input->GetInputBinding().AddKeyCommand("window.close", [=](){ glfwSetWindowShouldClose(mWindow, true); });
	input->GetInputBinding().AddKeyCommand("controls.save", [=](){ SaveInputMappingToFile("controls.mod", input->GetInputMapping()); });
	input->GetInputBinding().AddKeyCommand("window.fullscreen", [=](){ data.ToggleFullscreen(); });
	input->GetInputBinding().AddKeyCommand("window.save_settings", [=](){ SaveDisplayDataToFile("window.mod", &data); });
	
	scene = new Scene(input);
}

void Display::RequestFocus()
{
	glfwMakeContextCurrent(mWindow);
}

void Display::Run()
{
	scene->Initialize(data.GetAspectRatio());
	
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Set the minimum number of monitor refreshes the driver should wait from the time glfwSwapBuffers was called
	// before swapping the buffers to 1, preventing screen tearing and fixing frame rate to screen refresh rate.
	// May not be honored on all graphics card due to user-controlled settings or buggy graphics drivers.
	glfwSwapInterval(1);
	
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