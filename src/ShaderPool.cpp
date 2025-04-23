#include "ShaderPool.hpp"

ShaderPool::ShaderPool()
{
}

ShaderPool::~ShaderPool()
{
	
}

bool ShaderPool::AddShader(Shader* shader, std::string name)
{
	if (ContainsShader(name))
	{
		return false;
	}
	
	shaders.insert(std::pair(name, shader));
	return true;
}

bool ShaderPool::ContainsShader(std::string name)
{
	return shaders.count(name) != 0;
}

Shader* ShaderPool::RetrieveShader(std::string name)
{
	if (!ContainsShader(name))
	{
		return nullptr;
	}
	
	return shaders.at(name);
}

void ShaderPool::DeleteShader(std::string name)
{
	Shader* shader = RetrieveShader(name);
	shaders.erase(name);
	
	delete shader;
	shader = nullptr;
}

void ShaderPool::ClearShaders()
{
	for (auto &&pair : shaders)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	shaders.clear();
}

bool ShaderPool::AddShaderProgram(ShaderProgram* program, std::string name)
{
	if (ContainsShaderProgram(name))
	{
		return false;
	}
	
	programs.insert(std::pair(name, program));
	return true;
}

bool ShaderPool::ContainsShaderProgram(std::string name)
{
	return programs.count(name) != 0;
}

ShaderProgram* ShaderPool::RetrieveShaderProgram(std::string name)
{
	if (!ContainsShaderProgram(name))
	{
		return nullptr;
	}
	
	return programs.at(name);
}

void ShaderPool::DeleteShaderProgram(std::string name)
{
	ShaderProgram* program = RetrieveShaderProgram(name);
	programs.erase(name);
	
	delete program;
	program = nullptr;
}

void ShaderPool::ClearShaderPrograms()
{
	for (auto &&pair : programs)
	{
		delete pair.second;
		pair.second = nullptr;
	}
	programs.clear();
}