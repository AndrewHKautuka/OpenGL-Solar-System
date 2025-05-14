#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "DisplayData.hpp"
#include "DisplayDataFileUtil.hpp"
#include "Timer.h"
#include "InputListener.hpp"
#include "InputMappingFileUtil.hpp"
#include "Scene.hpp"

class Display
{
private:
	DisplayData data;
	GLFWmonitor* monitor;
public:
	static const double UPDATES_PER_SEC;
	static const double TARGET_DELTA_TIME;
	
	const float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	const char* const mTitle;
	GLFWwindow* const mWindow;
	
	Display(DisplayData pData, const char* pTitle);
	Display(GLFWmonitor* pMonitor, DisplayData pData, const char* pTitle);
	~Display();
	
	void Initialize();
	void RequestFocus();
	void Run();
private:
	Scene* scene;
	InputListener* input;
	InputMapping* inputMapping;
	
	Timer timer;
	
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};