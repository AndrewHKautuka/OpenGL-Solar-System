#pragma once

// glad is not used by InputBinding but regardless need to be included to ensure
// including GLFW does not throw a compilation error
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>

#include "InputMapping.hpp"

class InputBinding
{
private:
	bool* keysPressed;
	InputMapping* inputMapping;
	// Maps key, action and modifiers to Command (performed once on callback)
	std::unordered_map<std::string, std::function<void()>> keyCommandMap;
	// Maps key and key state to Action (performed every update)
	std::unordered_map<std::string, std::function<void()>> keyStateActionMap;
	std::function<void(double, double)> mouseMoveCommand = nullptr;
	std::function<void(double, double)> mouseScrollCommand = nullptr;
	std::pair<double, double> lastMousePosition;
	std::pair<double, double> lastMouseScroll;
public:
	InputBinding();
	~InputBinding();
	
	void Update();
	
	bool IsKeyPressedUnsafe(unsigned int key);
	bool IsKeyPressed(unsigned int key);
	KeyState GetKeyState(unsigned int key);
	
	void AddKeyStateAction(std::string actionName, std::function<void()> action);
	void RemoveKeyStateAction(std::string actionName);
	void ChangeKeyStateAction(std::string actionName, std::function<void()> action);
	
	void AddKeyCommand(std::string commandName, std::function<void()> command);
	void RemoveKeyCommand(std::string commandName);
	void ChangeKeyCommand(std::string commandName, std::function<void()> command);
	
	void SetMouseMoveCommand(std::function<void(double, double)> command);
	void UnsetMouseMoveCommand();
	
	void SetMouseScrollCommand(std::function<void(double, double)> command);
	void UnsetMouseScrollCommand();
	
	std::pair<double, double> GetLastMousePosition();
	std::pair<double, double> GetLastMouseScroll();
	
	void SetInputMapping(InputMapping* pInputMapping);
	
	void HandleKeyInput(int key, int action, int modifiers);
	void HandleMouseMoveInput(bool* firstMouseMoveEvent, double xPos, double yPos);
	void HandleMouseScrollInput(bool* firstMouseScrollEvent, double xScroll, double yScroll);
};