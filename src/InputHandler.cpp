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
}

void InputHandler::Unbind()
{
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

void InputHandler::AddStateAction(int key, KeyState state, std::function<void()> action)
{
	keyStateActionMap.insert(std::make_pair(std::make_tuple(key, state), action));
}

void InputHandler::RemoveStateAction(int key, KeyState state)
{
	keyStateActionMap.erase(std::make_tuple(key, state));
}

void InputHandler::ChangeStateAction(int key, KeyState state, std::function<void()> action)
{
	auto current = keyStateActionMap.find(std::make_tuple(key, state));
	
	if (current != keyStateActionMap.end())
	{
		current->second = action;
	}
}

void InputHandler::AddCommand(int key, int action, int modifiers, std::function<void()> command)
{
	keyCommandMap.insert(std::make_pair(std::make_tuple(key, action, modifiers), command));
}

void InputHandler::RemoveCommand(int key, int action, int modifiers)
{
	keyCommandMap.erase(std::make_tuple(key, action, modifiers));
}

void InputHandler::ChangeCommand(int key, int action, int modifiers, std::function<void()> command)
{
	auto current = keyCommandMap.find(std::make_tuple(key, action, modifiers));
	
	if (current != keyCommandMap.end())
	{
		current->second = command;
	}
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

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	((InputHandler*) glfwGetWindowUserPointer(window))->HandleKeyInput(key, action, modifiers);
}