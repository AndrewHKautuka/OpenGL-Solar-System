#include "Display.hpp"

#include "gLErrorHandle.hpp"

Display::Display(unsigned int pWidth, unsigned int pHeight, const char* pTitle) : mWidth(pWidth), mHeight(pHeight), mTitle(pTitle), mWindow(glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL))
{
	scene = nullptr;
}

Display::~Display()
{
	if (scene != nullptr)
	{
		delete scene;
		scene = nullptr;
	}
	
	// GLFW Termination
	glfwTerminate();
}

void Display::Initialize()
{
	GLCall(glViewport(0, 0, mWidth, mHeight));
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
	
	scene = new Scene;
}

void Display::RequestFocus()
{
	glfwMakeContextCurrent(mWindow);
}

void Display::Run()
{
	scene->Initialize();
	
	Texture sunTexture("textures/sunmap.jpg");
	Texture mercuryTexture("textures/mercurymap.jpg");
	Texture venusTexture("textures/venusmap.jpg");
	Texture earthTexture("textures/earthmap1k.jpg");
	Texture moonTexture("textures/moonmap1k.jpg", GL_RED);
	Texture marsTexture("textures/marsmap1k.jpg");
	
	Planet sun(1.0f, 18, sunTexture);
	Planet mercury(1.0f, 18, mercuryTexture);
	Planet venus(1.0f, 18, venusTexture);
	Planet earth(1.0f, 18, earthTexture);
	Planet moon(1.0f, 18, moonTexture);
	Planet mars(1.0f, 18, marsTexture);
	
	scene->AddPlanet(sun);
	scene->AddPlanet(mercury);
	scene->AddPlanet(venus);
	scene->AddPlanet(earth);
	scene->AddPlanet(moon);
	scene->AddPlanet(mars);
	
	// Render loop
	while (!glfwWindowShouldClose(mWindow))
	{
		GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		
		scene->Render();
		
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}
}

void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}