#include "InputMappingFileUtil.hpp"

#include <cstring>
#include <iostream>
#include <fstream>

void SaveInputMappingToFile(const char* path, InputMapping* inputMapping)
{
	std::ofstream file;
	file.open(path, std::ios::trunc);
	
	if (file.is_open())
	{
		auto stateActions = inputMapping->GetKeyStateActionMappings();
		
		for (auto it = stateActions.first; it != stateActions.second; it++)
		{
			unsigned int key;
			KeyState state;
			std::tie(key, state) = it->first;
			file << it->second << " = action(" << MapKeyValueToShorthand(key) << ", " << (state == RELEASED ? "release" : "press") << ")\n";
		}
		
		auto commands = inputMapping->GetKeyCpmmands();
		
		for (auto it = commands.first; it != commands.second; it++)
		{
			unsigned int key;
			unsigned int action;
			unsigned int modifiers;
			std::tie(key, action, modifiers) = it->first;
			file << it->second << " = command(" << MapKeyValueToShorthand(key) << ", " << (action == GLFW_RELEASE ? "release" : "press") << ", " << modifiers << ")\n";
		}
		
		file.close();
	}
	else
	{
		std::cerr << "Failed to open file \"" << path << "\" for writing" << std::endl;
	}
}

InputMapping* ReadInputMappingFromFile(const char* path)
{
	std::ifstream file;
	file.open(path);
	
	InputMapping* result = InputMapping::GetNewDefaultInputMapping();
	
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			TrimString(line);
			if (line == "")
			{
				continue;
			}
			
			auto statement = SplitString(line, '=');
			
			if (statement.size() != 2)
			{
				std::cerr << "Malformed line:\t\"" << line << "\"\n";
				continue;
			}
			
			auto name = statement[0];
			TrimString(name);
			
			auto mapping = SplitString(statement[1], '(');
			
			if (statement.size() != 2)
			{
				std::cerr << "Malformed mapping in:\t\"" << line << "\"\n";
				continue;
			}
			
			auto paramList = mapping[1];
			TrimString(paramList);
			if (paramList[paramList.size() - 1] != ')')
			{
				std::cerr << "Malformed mapping in:\t\"" << line << "\"\n";
				continue;
			}
			paramList = paramList.substr(0, paramList.size() - 1);
			
			auto type = TrimStringCopy(mapping[0]);
			auto params = SplitString(paramList, ',');
			
			if (type == "action")
			{
				if (params.size() != 2)
				{
					std::cerr << "Incorrect number of parameters in:\t\"" << line << "\"\n";
					continue;
				}
				
				TrimString(params[0]);
				TrimString(params[1]);
				
				const char* keyShorthand = params[0].c_str();
				
				if (params[1] == "release")
				{
					result->AddKeyStateAction(MapKeyShorthandToValue(keyShorthand), RELEASED, statement[0]);
					continue;
				}
				else if (params[1] == "press")
				{
					result->AddKeyStateAction(MapKeyShorthandToValue(keyShorthand), PRESSED, statement[0]);
					continue;
				}
				else
				{
					std::cerr << "Incorrect/unknown key state in:\t\"" << line << "\"\n";
					continue;
				}
			}
			else if (type == "command")
			{
				if (params.size() != 3)
				{
					std::cerr << "Incorrect number of parameters in:\t\"" << line << "\"\n";
					continue;
				}
				
				TrimString(params[0]);
				TrimString(params[1]);
				TrimString(params[2]);
				
				const char* keyShorthand = params[0].c_str();
				unsigned int modifiers = std::strtoul(params[2].c_str(), nullptr, 10);
				
				if (params[1] == "release")
				{
					result->AddKeyCommand(MapKeyShorthandToValue(keyShorthand), GLFW_RELEASE, modifiers, name);
					continue;
				}
				else if (params[1] == "press")
				{
					result->AddKeyCommand(MapKeyShorthandToValue(keyShorthand), GLFW_PRESS, modifiers, name);
					continue;
				}
				else
				{
					std::cerr << "Incorrect/unknown key state in:\t\"" << line << "\"\n";
					continue;
				}
			}
			else
			{
				std::cerr << "Incorrect/unknown input type in:\t\"" << line << "\"\n";
				continue;
			}
		}
		
		file.close();
	}
	else
	{
		std::cerr << "Failed to open file \"" << path << "\" for reading" << std::endl;
	}
	
	return result;
}

const char* MapKeyValueToShorthand(unsigned int keyValue)
{
	switch (keyValue)
	{
		case GLFW_KEY_A:
			return "a";
		case GLFW_KEY_B:
			return "b";
		case GLFW_KEY_C:
			return "c";
		case GLFW_KEY_D:
			return "d";
		case GLFW_KEY_E:
			return "e";
		case GLFW_KEY_F:
			return "f";
		case GLFW_KEY_G:
			return "g";
		case GLFW_KEY_H:
			return "h";
		case GLFW_KEY_I:
			return "i";
		case GLFW_KEY_J:
			return "j";
		case GLFW_KEY_K:
			return "k";
		case GLFW_KEY_L:
			return "l";
		case GLFW_KEY_M:
			return "m";
		case GLFW_KEY_N:
			return "n";
		case GLFW_KEY_O:
			return "o";
		case GLFW_KEY_P:
			return "p";
		case GLFW_KEY_Q:
			return "q";
		case GLFW_KEY_R:
			return "r";
		case GLFW_KEY_S:
			return "s";
		case GLFW_KEY_T:
			return "t";
		case GLFW_KEY_U:
			return "u";
		case GLFW_KEY_V:
			return "v";
		case GLFW_KEY_W:
			return "w";
		case GLFW_KEY_X:
			return "x";
		case GLFW_KEY_Y:
			return "y";
		case GLFW_KEY_Z:
			return "z";
		case GLFW_KEY_0:
			return "0";
		case GLFW_KEY_1:
			return "1";
		case GLFW_KEY_2:
			return "2";
		case GLFW_KEY_3:
			return "3";
		case GLFW_KEY_4:
			return "4";
		case GLFW_KEY_5:
			return "5";
		case GLFW_KEY_6:
			return "6";
		case GLFW_KEY_7:
			return "7";
		case GLFW_KEY_8:
			return "8";
		case GLFW_KEY_9:
			return "9";
		case GLFW_KEY_UP:
			return "up";
		case GLFW_KEY_DOWN:
			return "down";
		case GLFW_KEY_LEFT:
			return "left";
		case GLFW_KEY_RIGHT:
			return "right";
		case GLFW_KEY_SPACE:
			return "space";
		case GLFW_KEY_ENTER:
			return "enter";
		case GLFW_KEY_CAPS_LOCK:
			return "caps_lock";
		case GLFW_KEY_TAB:
			return "tab";
		case GLFW_KEY_PAGE_UP:
			return "page_up";
		case GLFW_KEY_PAGE_DOWN:
			return "page_down";
		case GLFW_KEY_HOME:
			return "home";
		case GLFW_KEY_END:
			return "end";
		case GLFW_KEY_BACKSPACE:
			return "backspace";
		case GLFW_KEY_DELETE:
			return "delete";
		case GLFW_KEY_INSERT:
			return "insert";
		case GLFW_KEY_SLASH:
			return "forward_slash";
		case GLFW_KEY_BACKSLASH:
			return "back_slash";
		case GLFW_KEY_ESCAPE:
			return "esc";
		case GLFW_KEY_GRAVE_ACCENT:
			return "grave_accent";
		case GLFW_KEY_EQUAL:
			return "equal";
		case GLFW_KEY_MINUS:
			return "minus";
		case GLFW_KEY_LEFT_BRACKET:
			return "left_bracket";
		case GLFW_KEY_RIGHT_BRACKET:
			return "right_bracket";
		case GLFW_KEY_SEMICOLON:
			return "semicolon";
		case GLFW_KEY_APOSTROPHE:
			return "apostrophe";
		case GLFW_KEY_COMMA:
			return "comma";
		case GLFW_KEY_PERIOD:
			return "period";
		case GLFW_KEY_F1:
			return "f1";
		case GLFW_KEY_F2:
			return "f2";
		case GLFW_KEY_F3:
			return "f3";
		case GLFW_KEY_F4:
			return "f4";
		case GLFW_KEY_F5:
			return "f5";
		case GLFW_KEY_F6:
			return "f6";
		case GLFW_KEY_F7:
			return "f7";
		case GLFW_KEY_F8:
			return "f8";
		case GLFW_KEY_F9:
			return "f9";
		case GLFW_KEY_F10:
			return "f10";
		case GLFW_KEY_F11:
			return "f11";
		case GLFW_KEY_F12:
			return "f12";
		case GLFW_KEY_F13:
			return "f13";
		case GLFW_KEY_F14:
			return "f14";
		case GLFW_KEY_F15:
			return "f15";
		case GLFW_KEY_F16:
			return "f16";
		case GLFW_KEY_F17:
			return "f17";
		case GLFW_KEY_F18:
			return "f18";
		case GLFW_KEY_F19:
			return "f19";
		case GLFW_KEY_F20:
			return "f20";
		case GLFW_KEY_F21:
			return "f21";
		case GLFW_KEY_F22:
			return "f22";
		case GLFW_KEY_F23:
			return "f23";
		case GLFW_KEY_F24:
			return "f24";
		case GLFW_KEY_F25:
			return "f25";
		case GLFW_KEY_LEFT_SHIFT:
			return "left_shift";
		case GLFW_KEY_LEFT_CONTROL:
			return "left_ctrl";
		case GLFW_KEY_LEFT_ALT:
			return "left_alt";
		case GLFW_KEY_LEFT_SUPER:
			return "left_super";
		case GLFW_KEY_RIGHT_SHIFT:
			return "right_shift";
		case GLFW_KEY_RIGHT_CONTROL:
			return "right_ctrl";
		case GLFW_KEY_RIGHT_ALT:
			return "right_alt";
		case GLFW_KEY_RIGHT_SUPER:
			return "right_super";
		default:
			return nullptr;
	}
}

unsigned int MapKeyShorthandToValue(const char* keyShorthand)
{
	if (strcmp(keyShorthand, "a") == 0)
	{
		return GLFW_KEY_A;
	}
	if (strcmp(keyShorthand, "b") == 0)
	{
		return GLFW_KEY_B;
	}
	if (strcmp(keyShorthand, "c") == 0)
	{
		return GLFW_KEY_C;
	}
	if (strcmp(keyShorthand, "d") == 0)
	{
		return GLFW_KEY_D;
	}
	if (strcmp(keyShorthand, "e") == 0)
	{
		return GLFW_KEY_E;
	}
	if (strcmp(keyShorthand, "f") == 0)
	{
		return GLFW_KEY_F;
	}
	if (strcmp(keyShorthand, "g") == 0)
	{
		return GLFW_KEY_G;
	}
	if (strcmp(keyShorthand, "h") == 0)
	{
		return GLFW_KEY_H;
	}
	if (strcmp(keyShorthand, "i") == 0)
	{
		return GLFW_KEY_I;
	}
	if (strcmp(keyShorthand, "j") == 0)
	{
		return GLFW_KEY_J;
	}
	if (strcmp(keyShorthand, "k") == 0)
	{
		return GLFW_KEY_K;
	}
	if (strcmp(keyShorthand, "l") == 0)
	{
		return GLFW_KEY_L;
	}
	if (strcmp(keyShorthand, "m") == 0)
	{
		return GLFW_KEY_M;
	}
	if (strcmp(keyShorthand, "n") == 0)
	{
		return GLFW_KEY_N;
	}
	if (strcmp(keyShorthand, "o") == 0)
	{
		return GLFW_KEY_O;
	}
	if (strcmp(keyShorthand, "p") == 0)
	{
		return GLFW_KEY_P;
	}
	if (strcmp(keyShorthand, "q") == 0)
	{
		return GLFW_KEY_Q;
	}
	if (strcmp(keyShorthand, "r") == 0)
	{
		return GLFW_KEY_R;
	}
	if (strcmp(keyShorthand, "s") == 0)
	{
		return GLFW_KEY_S;
	}
	if (strcmp(keyShorthand, "t") == 0)
	{
		return GLFW_KEY_T;
	}
	if (strcmp(keyShorthand, "u") == 0)
	{
		return GLFW_KEY_U;
	}
	if (strcmp(keyShorthand, "v") == 0)
	{
		return GLFW_KEY_V;
	}
	if (strcmp(keyShorthand, "w") == 0)
	{
		return GLFW_KEY_W;
	}
	if (strcmp(keyShorthand, "x") == 0)
	{
		return GLFW_KEY_X;
	}
	if (strcmp(keyShorthand, "y") == 0)
	{
		return GLFW_KEY_Y;
	}
	if (strcmp(keyShorthand, "z") == 0)
	{
		return GLFW_KEY_Z;
	}
	if (strcmp(keyShorthand, "0") == 0)
	{
		return GLFW_KEY_0;
	}
	if (strcmp(keyShorthand, "1") == 0)
	{
		return GLFW_KEY_1;
	}
	if (strcmp(keyShorthand, "2") == 0)
	{
		return GLFW_KEY_2;
	}
	if (strcmp(keyShorthand, "3") == 0)
	{
		return GLFW_KEY_3;
	}
	if (strcmp(keyShorthand, "4") == 0)
	{
		return GLFW_KEY_4;
	}
	if (strcmp(keyShorthand, "5") == 0)
	{
		return GLFW_KEY_5;
	}
	if (strcmp(keyShorthand, "6") == 0)
	{
		return GLFW_KEY_6;
	}
	if (strcmp(keyShorthand, "7") == 0)
	{
		return GLFW_KEY_7;
	}
	if (strcmp(keyShorthand, "8") == 0)
	{
		return GLFW_KEY_8;
	}
	if (strcmp(keyShorthand, "9") == 0)
	{
		return GLFW_KEY_9;
	}
	if (strcmp(keyShorthand, "up") == 0)
	{
		return GLFW_KEY_UP;
	}
	if (strcmp(keyShorthand, "down") == 0)
	{
		return GLFW_KEY_DOWN;
	}
	if (strcmp(keyShorthand, "left") == 0)
	{
		return GLFW_KEY_LEFT;
	}
	if (strcmp(keyShorthand, "right") == 0)
	{
		return GLFW_KEY_RIGHT;
	}
	if (strcmp(keyShorthand, "space") == 0)
	{
		return GLFW_KEY_SPACE;
	}
	if (strcmp(keyShorthand, "enter") == 0)
	{
		return GLFW_KEY_ENTER;
	}
	if (strcmp(keyShorthand, "caps_lock") == 0)
	{
		return GLFW_KEY_CAPS_LOCK;
	}
	if (strcmp(keyShorthand, "tab") == 0)
	{
		return GLFW_KEY_TAB;
	}
	if (strcmp(keyShorthand, "page_up") == 0)
	{
		return GLFW_KEY_PAGE_UP;
	}
	if (strcmp(keyShorthand, "page_down") == 0)
	{
		return GLFW_KEY_PAGE_DOWN;
	}
	if (strcmp(keyShorthand, "home") == 0)
	{
		return GLFW_KEY_HOME;
	}
	if (strcmp(keyShorthand, "end") == 0)
	{
		return GLFW_KEY_END;
	}
	if (strcmp(keyShorthand, "backspace") == 0)
	{
		return GLFW_KEY_BACKSPACE;
	}
	if (strcmp(keyShorthand, "delete") == 0)
	{
		return GLFW_KEY_DELETE;
	}
	if (strcmp(keyShorthand, "insert") == 0)
	{
		return GLFW_KEY_INSERT;
	}
	if (strcmp(keyShorthand, "forward_slash") == 0)
	{
		return GLFW_KEY_SLASH;
	}
	if (strcmp(keyShorthand, "back_slash") == 0)
	{
		return GLFW_KEY_BACKSLASH;
	}
	if (strcmp(keyShorthand, "esc") == 0)
	{
		return GLFW_KEY_ESCAPE;
	}
	if (strcmp(keyShorthand, "grave_accent") == 0)
	{
		return GLFW_KEY_GRAVE_ACCENT;
	}
	if (strcmp(keyShorthand, "equal") == 0)
	{
		return GLFW_KEY_EQUAL;
	}
	if (strcmp(keyShorthand, "minus") == 0)
	{
		return GLFW_KEY_MINUS;
	}
	if (strcmp(keyShorthand, "left_bracket") == 0)
	{
		return GLFW_KEY_LEFT_BRACKET;
	}
	if (strcmp(keyShorthand, "right_bracket") == 0)
	{
		return GLFW_KEY_RIGHT_BRACKET;
	}
	if (strcmp(keyShorthand, "semicolon") == 0)
	{
		return GLFW_KEY_SEMICOLON;
	}
	if (strcmp(keyShorthand, "apostrophe") == 0)
	{
		return GLFW_KEY_APOSTROPHE;
	}
	if (strcmp(keyShorthand, "comma") == 0)
	{
		return GLFW_KEY_COMMA;
	}
	if (strcmp(keyShorthand, "period") == 0)
	{
		return GLFW_KEY_PERIOD;
	}
	if (strcmp(keyShorthand, "f1") == 0)
	{
		return GLFW_KEY_F1;
	}
	if (strcmp(keyShorthand, "f2") == 0)
	{
		return GLFW_KEY_F2;
	}
	if (strcmp(keyShorthand, "f3") == 0)
	{
		return GLFW_KEY_F3;
	}
	if (strcmp(keyShorthand, "f4") == 0)
	{
		return GLFW_KEY_F4;
	}
	if (strcmp(keyShorthand, "f5") == 0)
	{
		return GLFW_KEY_F5;
	}
	if (strcmp(keyShorthand, "f6") == 0)
	{
		return GLFW_KEY_F6;
	}
	if (strcmp(keyShorthand, "f7") == 0)
	{
		return GLFW_KEY_F7;
	}
	if (strcmp(keyShorthand, "f8") == 0)
	{
		return GLFW_KEY_F8;
	}
	if (strcmp(keyShorthand, "f9") == 0)
	{
		return GLFW_KEY_F9;
	}
	if (strcmp(keyShorthand, "f10") == 0)
	{
		return GLFW_KEY_F10;
	}
	if (strcmp(keyShorthand, "f11") == 0)
	{
		return GLFW_KEY_F11;
	}
	if (strcmp(keyShorthand, "f12") == 0)
	{
		return GLFW_KEY_F12;
	}
	if (strcmp(keyShorthand, "f13") == 0)
	{
		return GLFW_KEY_F13;
	}
	if (strcmp(keyShorthand, "f14") == 0)
	{
		return GLFW_KEY_F14;
	}
	if (strcmp(keyShorthand, "f15") == 0)
	{
		return GLFW_KEY_F15;
	}
	if (strcmp(keyShorthand, "f16") == 0)
	{
		return GLFW_KEY_F16;
	}
	if (strcmp(keyShorthand, "f17") == 0)
	{
		return GLFW_KEY_F17;
	}
	if (strcmp(keyShorthand, "f18") == 0)
	{
		return GLFW_KEY_F18;
	}
	if (strcmp(keyShorthand, "f19") == 0)
	{
		return GLFW_KEY_F19;
	}
	if (strcmp(keyShorthand, "f20") == 0)
	{
		return GLFW_KEY_F20;
	}
	if (strcmp(keyShorthand, "f21") == 0)
	{
		return GLFW_KEY_F21;
	}
	if (strcmp(keyShorthand, "f22") == 0)
	{
		return GLFW_KEY_F22;
	}
	if (strcmp(keyShorthand, "f23") == 0)
	{
		return GLFW_KEY_F23;
	}
	if (strcmp(keyShorthand, "f24") == 0)
	{
		return GLFW_KEY_F24;
	}
	if (strcmp(keyShorthand, "f25") == 0)
	{
		return GLFW_KEY_F25;
	}
	if (strcmp(keyShorthand, "left_shift") == 0)
	{
		return GLFW_KEY_LEFT_SHIFT;
	}
	if (strcmp(keyShorthand, "left_ctrl") == 0)
	{
		return GLFW_KEY_LEFT_CONTROL;
	}
	if (strcmp(keyShorthand, "left_alt") == 0)
	{
		return GLFW_KEY_LEFT_ALT;
	}
	if (strcmp(keyShorthand, "left_super") == 0)
	{
		return GLFW_KEY_LEFT_SUPER;
	}
	if (strcmp(keyShorthand, "right_shift") == 0)
	{
		return GLFW_KEY_RIGHT_SHIFT;
	}
	if (strcmp(keyShorthand, "right_ctrl") == 0)
	{
		return GLFW_KEY_RIGHT_CONTROL;
	}
	if (strcmp(keyShorthand, "right_alt") == 0)
	{
		return GLFW_KEY_RIGHT_ALT;
	}
	if (strcmp(keyShorthand, "right_super") == 0)
	{
		return GLFW_KEY_RIGHT_SUPER;
	}
	
	return GLFW_KEY_UNKNOWN;
}