#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "util/gLErrorHandle.hpp"

Shader::Shader(const char* pShaderPath, ShaderType pType)
{
	std::string sourceCode;
	
	try
	{
		std::ifstream shaderFile(pShaderPath);
		
		std::stringstream shaderStream;
		
		shaderStream << shaderFile.rdbuf();
		
		shaderFile.close();
		
		sourceCode = shaderStream.str();
	}
	catch(const std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	
	const char* shaderCode = sourceCode.c_str();
	
	GLCall(ID = glCreateShader(getGLShaderType(pType)));
	GLCall(glShaderSource(ID, 1, &shaderCode, NULL));
	GLCall(glCompileShader(ID));
	
	checkShaderCompileErrors(pType);
}

Shader::~Shader()
{
	GLCall(glDeleteShader(ID));
}

void Shader::AttachShader(unsigned int shaderProgram)
{
	GLCall(glAttachShader(shaderProgram, ID));
}

void Shader::checkShaderCompileErrors(ShaderType type)
{
	int success;
	char infoLog[1024];
	
	GLCall(glGetShaderiv(ID, GL_COMPILE_STATUS, &success));
	
	if (!success)
	{
		GLCall(glGetShaderInfoLog(ID, 1024, NULL, infoLog));
		std::cout << "ERROR::SHADER::" << getShaderName(type) << "::COMPILATION_FAILED: " << infoLog << std::endl;
	}
}

GLenum Shader::getGLShaderType(ShaderType type)
{
	switch (type)
	{
		case VERTEX:
			return GL_VERTEX_SHADER;
		
		case FRAGMENT:
			return GL_FRAGMENT_SHADER;
		
		default:
			return 0xcccccccc;
	}
}

const char* Shader::getShaderName(ShaderType type)
{
	switch (type)
	{
		case VERTEX:
			return "VERTEX";
		
		case FRAGMENT:
			return "FRAGMENT";
		
		default:
			return "UNKNOWN";
	}
}