#include "InputMapping.hpp"

InputMapping::InputMapping()
{
	
}

InputMapping::~InputMapping()
{
	keyCommandMap.clear();
	keyStateActionMap.clear();
}

void InputMapping::Update()
{
	
}

void InputMapping::AddKeyStateAction(unsigned int key, KeyState state, std::string actionName)
{
	if (IsBlank(actionName))
	{
		return;
	}
	
	keyStateActionMap.insert(std::make_pair(std::make_tuple(key, state), actionName));
}

void InputMapping::RemoveKeyStateAction(unsigned int key, KeyState state)
{
	keyStateActionMap.erase(std::make_tuple(key, state));
}

void InputMapping::ChangeKeyStateAction(unsigned int key, KeyState state, std::string actionName)
{
	if (IsBlank(actionName))
	{
		return;
	}
	
	auto current = keyStateActionMap.find(std::make_tuple(key, state));
	
	if (current != keyStateActionMap.end())
	{
		current->second = actionName;
	}
}

std::string InputMapping::ResolveKeyStateAction(unsigned int key, KeyState state) const
{
	// Get iterator of key
	auto iterator = keyStateActionMap.find(std::make_tuple(key, state));
	// If not found (i.e. no mapping), then return (we are done)
	if (iterator == keyStateActionMap.end())
	{
		return "";
	}
	
	return iterator->second;
}

std::pair<std::unordered_map<std::tuple<unsigned int, KeyState>, std::string, hash_tuple::hash<std::tuple<unsigned int, KeyState>>>::iterator, std::unordered_map<std::tuple<unsigned int, KeyState>, std::string, hash_tuple::hash<std::tuple<unsigned int, KeyState>>>::iterator> InputMapping::GetKeyStateActionMappings()
{
	return std::make_pair(keyStateActionMap.begin(), keyStateActionMap.end());
}

void InputMapping::AddKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::string commandName)
{
	if (IsBlank(commandName))
	{
		return;
	}
	
	keyCommandMap.insert(std::make_pair(std::make_tuple(key, action, modifiers), commandName));
}

void InputMapping::RemoveKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers)
{
	keyCommandMap.erase(std::make_tuple(key, action, modifiers));
}

void InputMapping::ChangeKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers, std::string commandName)
{
	if (IsBlank(commandName))
	{
		return;
	}
	
	auto current = keyCommandMap.find(std::make_tuple(key, action, modifiers));
	
	if (current != keyCommandMap.end())
	{
		current->second = commandName;
	}
}

std::string InputMapping::ResolveKeyCommand(unsigned int key, unsigned int action, unsigned int modifiers) const
{
	// Get iterator of key
	auto iterator = keyCommandMap.find({ key, action, modifiers });
	// If not found (i.e. no mapping), then return (we are done)
	if (iterator == keyCommandMap.end())
	{
		return "";
	}
	
	return iterator->second;
}

std::pair<std::unordered_map<std::tuple<unsigned int, unsigned int, unsigned int>, std::string, hash_tuple::hash<std::tuple<unsigned int, unsigned int, unsigned int>>>::iterator, std::unordered_map<std::tuple<unsigned int, unsigned int, unsigned int>, std::string, hash_tuple::hash<std::tuple<unsigned int, unsigned int, unsigned int>>>::iterator> InputMapping::GetKeyCpmmands()
{
	return std::make_pair(keyCommandMap.begin(), keyCommandMap.end());
}

bool InputMapping::IsBlank(std::string string)
{
	return string == "";
}

InputMapping* InputMapping::GetNewDefaultInputMapping()
{
	InputMapping* defaultInputMapping = new InputMapping();
	
	// Camera Movement Controls
	defaultInputMapping->AddKeyStateAction(GLFW_KEY_W, PRESSED, "camera.move.forward");
	defaultInputMapping->AddKeyStateAction(GLFW_KEY_S, PRESSED, "camera.move.backward");
	defaultInputMapping->AddKeyStateAction(GLFW_KEY_A, PRESSED, "camera.move.left");
	defaultInputMapping->AddKeyStateAction(GLFW_KEY_D, PRESSED, "camera.move.right");
	
	// Special Controls
	defaultInputMapping->AddKeyCommand(GLFW_KEY_LEFT, RELEASED, GLFW_MOD_NONE, "moon.orbit.speed_up");
	defaultInputMapping->AddKeyCommand(GLFW_KEY_RIGHT, RELEASED, GLFW_MOD_NONE, "moon.orbit.speed_down");
	defaultInputMapping->AddKeyCommand(GLFW_KEY_UP, RELEASED, GLFW_MOD_NONE, "sun.spin.speed_up");
	defaultInputMapping->AddKeyCommand(GLFW_KEY_DOWN, RELEASED, GLFW_MOD_NONE, "sun.spin.speed_down");
	
	// Window Controls
	defaultInputMapping->AddKeyCommand(GLFW_KEY_ESCAPE, RELEASED, GLFW_MOD_NONE, "window.close");
	defaultInputMapping->AddKeyCommand(GLFW_KEY_F11, RELEASED, GLFW_MOD_NONE, "window.fullscreen");
	defaultInputMapping->AddKeyCommand(GLFW_KEY_V, RELEASED, GLFW_MOD_CONTROL, "window.save_settings");
	
	// Bindings Controls
	defaultInputMapping->AddKeyCommand(GLFW_KEY_C, RELEASED, GLFW_MOD_CONTROL, "controls.save");
	
	return defaultInputMapping;
}