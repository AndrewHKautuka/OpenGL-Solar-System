#pragma once

#include <glad/glad.h>
#include <string>

enum ShaderType
{
	VERTEX = 1, FRAGMENT
};

class Shader
{
public:
	Shader(const char* pShaderPath, ShaderType pType);
	~Shader();
	
	void AttachShader(unsigned int shaderProgram);
private:
	unsigned int ID;
	
	void checkShaderCompileErrors(ShaderType type);
	static GLenum getGLShaderType(ShaderType type);
	static const char* getShaderName(ShaderType type);
};