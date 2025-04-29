#include "InputHandler.hpp"

InputHandler::InputHandler(GLFWwindow* pWindow)
{
	window = pWindow;
	keysPressed = new bool[GLFW_KEY_LAST + 1];
	
	for (unsigned int i = 0; i < GLFW_KEY_LAST + 1; i++)
	{
		keysPressed[i] = false;
	}
}

InputHandler::~InputHandler()
{
	keyCommandMap.clear();
	keyStateActionMap.clear();
}

void InputHandler::Bind()
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
}

void InputHandler::Unbind()
{
	glfwSetScrollCallback(window, nullptr);
	glfwSetCursorPosCallback(window, nullptr);
	glfwSetKeyCallback(window, nullptr);
	glfwSetWindowUserPointer(window, nullptr);
}

void InputHandler::Update()
{
	for (unsigned int i = 0; i < GLFW_KEY_LAST + 1; i++)
	{
		if (keysPressed[i])
		{
			auto current = keyStateActionMap.find(std::make_tuple(i, PRESSED));
			
			if (current != keyStateActionMap.end())
			{
				current->second();
			}
		} else {
			auto current = keyStateActionMap.find(std::make_tuple(i, RELEASED));
			
			if (current != keyStateActionMap.end())
			{
				current->second();
			}
		}
	}
}

KeyState InputHandler::GetKeyState(int key)
{
	return keysPressed[key] ? PRESSED : RELEASED;
}

void InputHandler::AddKeyStateAction(int key, KeyState state, std::function<void()> action)
{
	keyStateActionMap.insert(std::make_pair(std::make_tuple(key, state), action));
}

void InputHandler::RemoveKeyStateAction(int key, KeyState state)
{
	keyStateActionMap.erase(std::make_tuple(key, state));
}

void InputHandler::ChangeKeyStateAction(int key, KeyState state, std::function<void()> action)
{
	auto current = keyStateActionMap.find(std::make_tuple(key, state));
	
	if (current != keyStateActionMap.end())
	{
		current->second = action;
	}
}

void InputHandler::AddKeyCommand(int key, int action, int modifiers, std::function<void()> command)
{
	keyCommandMap.insert(std::make_pair(std::make_tuple(key, action, modifiers), command));
}

void InputHandler::RemoveKeyCommand(int key, int action, int modifiers)
{
	keyCommandMap.erase(std::make_tuple(key, action, modifiers));
}

void InputHandler::ChangeKeyCommand(int key, int action, int modifiers, std::function<void()> command)
{
	auto current = keyCommandMap.find(std::make_tuple(key, action, modifiers));
	
	if (current != keyCommandMap.end())
	{
		current->second = command;
	}
}

void InputHandler::SetMouseMoveCommand(std::function<void(double, double)> command)
{
	mouseMoveCommand = command;
}

void InputHandler::UnsetMouseMoveCommand()
{
	mouseMoveCommand = nullptr;
}

void InputHandler::SetMouseScrollCommand(std::function<void(double, double)> command)
{
	mouseScrollCommand = command;
}

void InputHandler::UnsetMouseScrollCommand()
{
	mouseScrollCommand = nullptr;
}

std::pair<double, double> InputHandler::GetLastMousePosition()
{
	return lastMousePosition;
}

std::pair<double, double> InputHandler::GetLastMouseScroll()
{
	return lastMouseScroll;
}

void InputHandler::HandleKeyInput(int key, int action, int modifiers)
{
	if (action == GLFW_PRESS)
	{
		keysPressed[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keysPressed[key] = false;
	}
	
	// Get iterator of key
	auto iterator = keyCommandMap.find(std::make_tuple(key, action, modifiers));
	// If not found (i.e. no mapping), then return (we are done)
	if (iterator == keyCommandMap.end())
	{
		return;
	}
	
	// Otherwise execute command
	iterator->second();
}

void InputHandler::HandleMouseMoveInput(double xPos, double yPos)
{
	if (firstMouseMoveEvent)
	{
		lastMousePosition = std::make_pair(xPos, yPos);
		firstMouseMoveEvent = false;
	}
	
	if (mouseMoveCommand != nullptr)
	{
		mouseMoveCommand(xPos, yPos);
	}
	
	lastMousePosition = std::make_pair(xPos, yPos);
}

void InputHandler::HandleMouseScrollInput(double xScroll, double yScroll)
{
	if (firstMouseScrollEvent)
	{
		lastMouseScroll = std::make_pair(xScroll, yScroll);
		firstMouseScrollEvent = false;
	}
	
	if (mouseScrollCommand != nullptr)
	{
		mouseScrollCommand(xScroll, xScroll);
	}
	
	lastMouseScroll = std::make_pair(xScroll, yScroll);
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	((InputHandler*) glfwGetWindowUserPointer(window))->HandleKeyInput(key, action, modifiers);
}

void InputHandler::mouse_move_callback(GLFWwindow* window, double xPos, double yPos)
{
	((InputHandler*) glfwGetWindowUserPointer(window))->HandleMouseMoveInput(xPos, yPos);
}

void InputHandler::mouse_scroll_callback(GLFWwindow* window, double xScroll, double yScroll)
{
	((InputHandler*) glfwGetWindowUserPointer(window))->HandleMouseScrollInput(xScroll, yScroll);
}