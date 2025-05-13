#pragma once

// glad is not used by InputMapping but regardless need to be included to ensure
// including GLFW does not throw a compilation error
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <tuple>
#include <string>

#include "hash_tuple.hpp"

enum KeyState
{
	RELEASED, PRESSED
};

class InputMapping
{
private:
	// Maps key, action and modifiers to Command (performed once on callback)
	std::unordered_map<std::tuple<unsigned int, unsigned int, unsigned int>, std::string, hash_tuple::hash<std::tuple<unsigned int, unsigned int, unsigned int>>> keyCommandMap;
	// Maps key and key state to Action (performed every update)
	std::unordered_map<std::tuple<unsigned int, KeyState>, std::string, hash_tuple::hash<std::tuple<unsigned int, KeyState>>> keyStateActionMap;
	
	InputMapping();
public:
	~InputMapping();
	
	void Update();
	
	void AddKeyStateAction(unsigned int key, KeyState state, std::string actionName);
	void RemoveKeyStateAction(unsigned int key, KeyState state);
	void ChangeKeyStateAction(unsigned int key, KeyState state, std::string actionName);
	std::string ResolveKeyStateAction(unsigned int key, KeyState state) const;
	
	void AddKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::string commandName);
	void RemoveKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers);
	void ChangeKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::string commandName);
	std::string ResolveKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers) const;
	
	static bool IsBlank(std::string string);
	static InputMapping* GetNewDefaultInputMapping();
};

// Only define GLFW_MOD_NONE if it is not already defined
// If no modifier flag for no modifier (purely for readability)
#ifndef GLFW_MOD_NONE
// Represents no modifier bits have been set
#define GLFW_MOD_NONE 0
#endif