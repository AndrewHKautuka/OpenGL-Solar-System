// Reference: https://www.glfw.org/docs/3.3/input_guide.html
#pragma once

// glad is not used by InputHandler but regardless need to be included to ensure
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

class InputHandler
{
private:
	GLFWwindow* window;
	bool* keysPressed;
	// Maps key, action and modifiers to Command (performed once on callback)
	std::unordered_map<std::tuple<int, int, int>, std::function<void()>, hash_tuple::hash<std::tuple<int, int, int>>> keyCommandMap;
	// Maps key and key state to Action (performed every update)
	std::unordered_map<std::tuple<int, KeyState>, std::function<void()>, hash_tuple::hash<std::tuple<int, KeyState>>> keyStateActionMap;
public:
	InputHandler(GLFWwindow* pWindow);
	~InputHandler();
	
	void Bind();
	void Unbind();
	
	void Update();
	
	KeyState GetKeyState(int key);
	
	void AddStateAction(int key, KeyState state, std::function<void()> action);
	void RemoveStateAction(int key, KeyState state);
	void ChangeStateAction(int key, KeyState state, std::function<void()> action);
	
	void AddCommand(int key, int action, int modifiers, std::function<void()> command);
	void RemoveCommand(int key, int action, int modifiers);
	void ChangeCommand(int key, int action, int modifiers, std::function<void()> command);
private:
	void HandleKeyInput(int key, int action, int modifiers);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
};

// Only define GLFW_MOD_NONE if it is not already defined
// If no modifier flag for no modifier (purely for readability)
#ifndef GLFW_MOD_NONE
// Represents no modifier bits have been set
#define GLFW_MOD_NONE 0
#endif