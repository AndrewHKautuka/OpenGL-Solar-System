#include "InputListener.hpp"

InputListener::InputListener(GLFWwindow* pWindow)
{
	window = pWindow;
}

InputListener::~InputListener()
{
}

void InputListener::Bind()
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
}

void InputListener::Unbind()
{
	glfwSetScrollCallback(window, nullptr);
	glfwSetCursorPosCallback(window, nullptr);
	glfwSetKeyCallback(window, nullptr);
	glfwSetWindowUserPointer(window, nullptr);
}

void InputListener::Update()
{
	if (inputBinding != nullptr)
	{
		inputBinding->Update();
	}
}

void InputListener::SetInputBinding(InputBinding* pInputBinding)
{
	if (pInputBinding != nullptr && inputBinding == nullptr)
	{
		delete inputBinding;
	}
	inputBinding = pInputBinding;
}

InputBinding* InputListener::GetInputBinding()
{
	return inputBinding;
}

void InputListener::key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	((InputListener*) glfwGetWindowUserPointer(window))->inputBinding->HandleKeyInput(key, action, modifiers);
}

void InputListener::mouse_move_callback(GLFWwindow* window, double xPos, double yPos)
{
	InputListener* inputListener = ((InputListener*) glfwGetWindowUserPointer(window));
	if (inputListener->inputBinding != nullptr)
	{
		inputListener->inputBinding->HandleMouseMoveInput(&inputListener->firstMouseMoveEvent, xPos, yPos);
	}
}

void InputListener::mouse_scroll_callback(GLFWwindow* window, double xScroll, double yScroll)
{
	InputListener* inputListener = ((InputListener*) glfwGetWindowUserPointer(window));
	if (inputListener->inputBinding != nullptr)
	{
		inputListener->inputBinding->HandleMouseScrollInput(&inputListener->firstMouseScrollEvent, xScroll, yScroll);
	}
}