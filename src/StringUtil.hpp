#pragma once

#include <string>
#include <vector>

void LeftTrimString(std::string& string);
void RightTrimString(std::string& string);
void TrimString(std::string& string);

std::string LeftTrimStringCopy(const std::string& string);
std::string RightTrimStringCopy(const std::string& string);
std::string TrimStringCopy(const std::string& string);

std::pair<std::string, std::string> SplitStringOnFirst(std::string string, char delimiter);
std::vector<std::string> SplitString(std::string string, char delimiter);