#include "ShaderProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "gLErrorHandle.hpp"

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader)
{
	GLCall(ID = glCreateProgram());
	vertexShader.AttachShader(ID);
	fragmentShader.AttachShader(ID);
	GLCall(glLinkProgram(ID));
	
	checkProgramLinkErrors();
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(ID));
}

void ShaderProgram::use()
{
	GLCall(glUseProgram(ID));
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
	GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value));
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
	GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	GLCall(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

void ShaderProgram::setVec3(const std::string& name, glm::vec3 value) const
{
	GLCall(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)));
}

void ShaderProgram::setMat4(const std::string& name, glm::mat4 value) const
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)));
}

void ShaderProgram::checkProgramLinkErrors()
{
	int success;
	char infoLog[1024];
	
	GLCall(glGetProgramiv(ID, GL_LINK_STATUS, &success));
	
	if (!success)
	{
		GLCall(glGetProgramInfoLog(ID, 512, NULL, infoLog));
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << infoLog << std::endl;
	}
}