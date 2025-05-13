#include "InputListener.hpp"

InputListener::InputListener(GLFWwindow* pWindow)
{
	window = pWindow;
	inputMapping = nullptr;
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
	inputBinding.Update();
}

InputBinding& InputListener::GetInputBinding()
{
	return inputBinding;
}

void InputListener::SetInputMapping(InputMapping* pInputMapping)
{
	if (pInputMapping == nullptr)
	{
		return;
	}
	
	if (inputMapping != nullptr)
	{
		delete inputMapping;
	}
	inputMapping = pInputMapping;
	inputBinding.SetInputMapping(pInputMapping);
}

InputMapping* InputListener::GetInputMapping()
{
	return inputMapping;
}

void InputListener::key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	((InputListener*) glfwGetWindowUserPointer(window))->inputBinding.HandleKeyInput(key, action, modifiers);
}

void InputListener::mouse_move_callback(GLFWwindow* window, double xPos, double yPos)
{
	InputListener* inputListener = ((InputListener*) glfwGetWindowUserPointer(window));
	inputListener->inputBinding.HandleMouseMoveInput(&inputListener->firstMouseMoveEvent, xPos, yPos);
}

void InputListener::mouse_scroll_callback(GLFWwindow* window, double xScroll, double yScroll)
{
	InputListener* inputListener = ((InputListener*) glfwGetWindowUserPointer(window));
	inputListener->inputBinding.HandleMouseScrollInput(&inputListener->firstMouseScrollEvent, xScroll, yScroll);
}