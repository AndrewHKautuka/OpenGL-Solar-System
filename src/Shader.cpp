#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "gLErrorHandle.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	
	try
	{
		std::ifstream vShaderFile(vertexPath);
		std::ifstream fShaderFile(fragmentPath);
		
		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		vShaderFile.close();
		fShaderFile.close();
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(const std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	unsigned int vertex, fragment;
	
	GLCall(vertex = glCreateShader(GL_VERTEX_SHADER));
	GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
	GLCall(glCompileShader(vertex));
	
	checkShaderCompileErrors(vertex, "VERTEX");
	
	GLCall(fragment = glCreateShader(GL_FRAGMENT_SHADER));
	GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
	GLCall(glCompileShader(fragment));
	
	checkShaderCompileErrors(fragment, "FRAGMENT");
	
	GLCall(ID = glCreateProgram());
	GLCall(glAttachShader(ID, vertex));
	GLCall(glAttachShader(ID, fragment));
	GLCall(glLinkProgram(ID));
	
	checkProgramLinkErrors(ID);
	
	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));
}

Shader::~Shader()
{
	// GLCall(glDeleteProgram(ID));
}

void Shader::use()
{
	GLCall(glUseProgram(ID));
}

void Shader::setBool(const std::string& name, bool value) const
{
	GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value));
}

void Shader::setInt(const std::string& name, int value) const
{
	GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}

void Shader::setFloat(const std::string& name, float value) const
{
	GLCall(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::checkShaderCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
	
	if (!success)
	{
		GLCall(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
		std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED: " << infoLog << std::endl;
	}
}

void Shader::checkProgramLinkErrors(unsigned int shaderProgram)
{
	int success;
	char infoLog[1024];
	
	GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
	
	if (!success)
	{
		GLCall(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
	}
}