#pragma once

#include "StringUtil.hpp"
#include "DisplayData.hpp"

void SaveDisplayDataToFile(const char* path, const DisplayData* displayData);
DisplayData* ReadDisplayDataFromFile(const char* path, const GLFWvidmode* vidmode);