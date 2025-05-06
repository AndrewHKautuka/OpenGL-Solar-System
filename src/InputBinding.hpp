#pragma once

// glad is not used by InputBinding but regardless need to be included to ensure
// including GLFW does not throw a compilation error
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <tuple>
#include <functional>

#include "hash_tuple.hpp"

enum KeyState
{
	RELEASED, PRESSED
};

class InputBinding
{
private:
	bool* keysPressed;
	// Maps key, action and modifiers to Command (performed once on callback)
	std::unordered_map<std::tuple<unsigned int, unsigned int, unsigned int>, std::function<void()>, hash_tuple::hash<std::tuple<unsigned int, unsigned int, unsigned int>>> keyCommandMap;
	// Maps key and key state to Action (performed every update)
	std::unordered_map<std::tuple<unsigned int, KeyState>, std::function<void()>, hash_tuple::hash<std::tuple<unsigned int, KeyState>>> keyStateActionMap;
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
	
	void AddKeyStateAction(unsigned int key, KeyState state, std::function<void()> action);
	void RemoveKeyStateAction(unsigned int key, KeyState state);
	void ChangeKeyStateAction(unsigned int key, KeyState state, std::function<void()> action);
	
	void AddKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::function<void()> command);
	void RemoveKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers);
	void ChangeKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::function<void()> command);
	
	void SetMouseMoveCommand(std::function<void(double, double)> command);
	void UnsetMouseMoveCommand();
	
	void SetMouseScrollCommand(std::function<void(double, double)> command);
	void UnsetMouseScrollCommand();
	
	std::pair<double, double> GetLastMousePosition();
	std::pair<double, double> GetLastMouseScroll();
	
	void HandleKeyInput(int key, int action, int modifiers);
	void HandleMouseMoveInput(bool* firstMouseMoveEvent, double xPos, double yPos);
	void HandleMouseScrollInput(bool* firstMouseScrollEvent, double xScroll, double yScroll);
};

// Only define GLFW_MOD_NONE if it is not already defined
// If no modifier flag for no modifier (purely for readability)
#ifndef GLFW_MOD_NONE
// Represents no modifier bits have been set
#define GLFW_MOD_NONE 0
#endif