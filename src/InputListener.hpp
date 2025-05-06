// Reference: https://www.glfw.org/docs/3.3/input_guide.html
#pragma once

#include "InputBinding.hpp"

class InputListener
{
private:
	GLFWwindow* window;
	InputBinding* inputBinding;
	bool firstMouseMoveEvent = true, firstMouseScrollEvent = true;
public:
	InputListener(GLFWwindow* pWindow);
	~InputListener();
	
	void Bind();
	void Unbind();
	
	void Update();
	
	void SetInputBinding(InputBinding* pInputBinding);
	InputBinding* GetInputBinding();
private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
	static void mouse_move_callback(GLFWwindow* window, double xPos, double yPos);
	static void mouse_scroll_callback(GLFWwindow* window, double xScroll, double yScroll);
};