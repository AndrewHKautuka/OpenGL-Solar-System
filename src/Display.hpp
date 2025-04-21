#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display
{
public:
	unsigned int mWidth, mHeight;
	
	const float clearColor[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
	const char* const mTitle;
	GLFWwindow* const mWindow;
public:
	Display(unsigned int pWidth, unsigned int pHeight, const char* pTitle);
	~Display();
	
	void Initialize();
	void RequestFocus();
	void Run();
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};