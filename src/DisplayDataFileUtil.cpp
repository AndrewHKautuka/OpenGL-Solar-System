#include "DisplayDataFileUtil.hpp"

#include <cstring>
#include <iostream>
#include <fstream>

void SaveDisplayDataToFile(const char* path, const DisplayData* displayData)
{
	std::ofstream file;
	file.open(path, std::ios::trunc);
	
	if (file.is_open())
	{
		file << "resolution = (" << displayData->GetWidth() << ", " << displayData->GetHeight() << ")\n";
		file << "fullscreen_mode = " << (displayData->IsFullscreen() ? "true" : "false") << "\n";
		
		file.close();
	}
	else
	{
		std::cerr << "Failed to open file \"" << path << "\" for writing" << std::endl;
	}
}

DisplayData* ReadDisplayDataFromFile(const char* path, const GLFWvidmode* vidmode)
{
	std::ifstream file;
	file.open(path);
	
	DisplayData* result = new DisplayData(vidmode);
	
	if (result == nullptr)
	{
		std::cerr << "Could not allocate an instance of DisplayData\n";
		return nullptr;
	}
	
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
			auto value = statement[1];
			TrimString(name);
			TrimString(value);
			
			if (name == "resolution")
			{
				if ((value[0] != '(') || (value[value.size() - 1] != ')'))
				{
					std::cerr << "Malformed resolution value in:\t\"" << line << "\"\n";
					continue;
				}
				
				auto resolution = SplitString(value.substr(1, value.size() - 2), ',');
				
				if (resolution.size() != 2)
				{
					std::cerr << "Incorrect number of resolution components in:\t\"" << line << "\"\n";
					continue;
				}
				
				TrimString(resolution[0]);
				TrimString(resolution[1]);
				
				unsigned int width = std::strtoul(resolution[0].c_str(), nullptr, 10);
				unsigned int height = std::strtoul(resolution[1].c_str(), nullptr, 10);
				
				if (width == 0 || width > DisplayData::MAX_WIDTH)
				{
					std::cerr << "Invalid width in:\t\"" << line << "\"\n";
					continue;
				}
				else if (height == 0 || height > DisplayData::MAX_HEIGHT)
				{
					std::cerr << "Invalid height in:\t\"" << line << "\"\n";
					continue;
				}
				else
				{
					result->SetDimensions(width, height);
					continue;
				}
			}
			else if (name == "fullscreen_mode")
			{
				if (value == "true")
				{
					result->SetFullscreen(true);
					continue;
				}
				else if (value == "false")
				{
					result->SetFullscreen(false);
					continue;
				}
				else
				{
					std::cerr << "Incorrect/unknown fullscreen value in:\t\"" << line << "\"\n";
					continue;
				}
			}
			else
			{
				std::cerr << "Incorrect/unknown attribute name in:\t\"" << line << "\"\n";
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