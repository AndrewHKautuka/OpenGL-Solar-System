#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Timer.h"
#include "InputHandler.hpp"
#include "Scene.hpp"

class Display
{
public:
	static const double UPDATES_PER_SEC;
	static const double TARGET_DELTA_TIME;
	
	unsigned int mWidth, mHeight;
	
	const float clearColor[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
	const char* const mTitle;
	GLFWwindow* const mWindow;
	
	Display(unsigned int pWidth, unsigned int pHeight, const char* pTitle);
	~Display();
	
	void Initialize();
	void RequestFocus();
	void Run();
private:
	Scene* scene;
	InputHandler* input;
	
	Timer timer;
	
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};