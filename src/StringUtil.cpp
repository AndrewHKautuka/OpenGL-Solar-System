// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
#include "StringUtil.hpp"

#include <algorithm>
#include <sstream>

void LeftTrimString(std::string& string)
{
	string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](unsigned char ch){
		return !std::isspace(ch);
	}));
}

void RightTrimString(std::string& string)
{
	string.erase(std::find_if(string.rbegin(), string.rend(), [](unsigned char ch){
		return !std::isspace(ch);
	}).base(), string.end());
}

void TrimString(std::string& string)
{
	LeftTrimString(string);
	RightTrimString(string);
}

std::string LeftTrimStringCopy(const std::string& string)
{
	std::string temp(string);
	LeftTrimString(temp);
	return temp;
}

std::string RightTrimStringCopy(const std::string& string)
{
	std::string temp(string);
	RightTrimString(temp);
	return temp;
}

std::string TrimStringCopy(const std::string& string)
{
	std::string temp(string);
	TrimString(temp);
	return temp;
}

std::pair<std::string, std::string> SplitStringOnFirst(std::string string, char delimiter)
{
	auto pos = string.find_first_of(delimiter);
	
	std::string temp1 = string.substr(0, pos);
	std::string temp2 = string.substr(pos + 1);
	
	return { temp1, temp2 };
}

std::vector<std::string> SplitString(std::string string, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(string);
	
	std::string temp;
	while (std::getline(ss, temp, delimiter))
	{
		result.push_back(temp);
	}
	
	return result;
}