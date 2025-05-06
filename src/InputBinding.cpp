#include "InputBinding.hpp"

InputBinding::InputBinding()
{
	keysPressed = new bool[GLFW_KEY_LAST + 1];
	for (unsigned int i = 0; i < GLFW_KEY_LAST + 1; i++)
	{
		keysPressed[i] = false;
	}
}

InputBinding::~InputBinding()
{
	keyCommandMap.clear();
	keyStateActionMap.clear();
}

void InputBinding::Update()
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

bool InputBinding::IsKeyPressedUnsafe(unsigned int key)
{
	return keysPressed[key];
}

bool InputBinding::IsKeyPressed(unsigned int key)
{
	if (key > GLFW_KEY_LAST)
	{
		return false;
	}
	
	return keysPressed[key];
}

KeyState InputBinding::GetKeyState(unsigned int key)
{
	return keysPressed[key] ? PRESSED : RELEASED;
}

void InputBinding::AddKeyStateAction(unsigned int key, KeyState state, std::function<void()> action)
{
	keyStateActionMap.insert(std::make_pair(std::make_tuple(key, state), action));
}

void InputBinding::RemoveKeyStateAction(unsigned int key, KeyState state)
{
	keyStateActionMap.erase(std::make_tuple(key, state));
}

void InputBinding::ChangeKeyStateAction(unsigned int key, KeyState state, std::function<void()> action)
{
	auto current = keyStateActionMap.find(std::make_tuple(key, state));
	
	if (current != keyStateActionMap.end())
	{
		current->second = action;
	}
}

void InputBinding::AddKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::function<void()> command)
{
	keyCommandMap.insert(std::make_pair(std::make_tuple(key, action, modifiers), command));
}

void InputBinding::RemoveKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers)
{
	keyCommandMap.erase(std::make_tuple(key, action, modifiers));
}

void InputBinding::ChangeKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::function<void()> command)
{
	auto current = keyCommandMap.find(std::make_tuple(key, action, modifiers));
	
	if (current != keyCommandMap.end())
	{
		current->second = command;
	}
}

void InputBinding::SetMouseMoveCommand(std::function<void(double, double)> command)
{
	mouseMoveCommand = command;
}

void InputBinding::UnsetMouseMoveCommand()
{
	mouseMoveCommand = nullptr;
}

void InputBinding::SetMouseScrollCommand(std::function<void(double, double)> command)
{
	mouseScrollCommand = command;
}

void InputBinding::UnsetMouseScrollCommand()
{
	mouseScrollCommand = nullptr;
}

std::pair<double, double> InputBinding::GetLastMousePosition()
{
	return lastMousePosition;
}

std::pair<double, double> InputBinding::GetLastMouseScroll()
{
	return lastMouseScroll;
}

void InputBinding::HandleKeyInput(int key, int action, int modifiers)
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

void InputBinding::HandleMouseMoveInput(bool* firstMouseMoveEvent, double xPos, double yPos)
{
	if (*firstMouseMoveEvent)
	{
		lastMousePosition = std::make_pair(xPos, yPos);
		*firstMouseMoveEvent = false;
		return;
	}
	
	if (mouseMoveCommand != nullptr)
	{
		mouseMoveCommand(xPos, yPos);
	}
	
	lastMousePosition = std::make_pair(xPos, yPos);
}

void InputBinding::HandleMouseScrollInput(bool* firstMouseScrollEvent, double xScroll, double yScroll)
{
	if (*firstMouseScrollEvent)
	{
		lastMouseScroll = std::make_pair(xScroll, yScroll);
		*firstMouseScrollEvent = false;
		return;
	}
	
	if (mouseScrollCommand != nullptr)
	{
		mouseScrollCommand(xScroll, xScroll);
	}
	
	lastMouseScroll = std::make_pair(xScroll, yScroll);
}