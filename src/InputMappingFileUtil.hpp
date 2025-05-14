#pragma once

#include "StringUtil.hpp"
#include "InputMapping.hpp"

void SaveInputMappingToFile(const char* path, InputMapping* inputMapping);
InputMapping* ReadInputMappingFromFile(const char* path);

const char* MapKeyValueToShorthand(unsigned int keyValue);
unsigned int MapKeyShorthandToValue(const char* keyShorthand);