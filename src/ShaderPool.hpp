#pragma once

#include <unordered_map>
#include <string>

#include "ShaderProgram.hpp"

class ShaderPool
{
public:
	ShaderPool();
	~ShaderPool();
	
	bool AddShader(Shader* shader, std::string name);
	bool ContainsShader(std::string name) const;
	Shader* RetrieveShader(std::string name) const;
	void DeleteShader(std::string name);
	void ClearShaders();
	
	bool AddShaderProgram(ShaderProgram* program, std::string name);
	bool ContainsShaderProgram(std::string name) const;
	ShaderProgram* RetrieveShaderProgram(std::string name) const;
	void DeleteShaderProgram(std::string name);
	void ClearShaderPrograms();
private:
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, ShaderProgram*> programs;
};