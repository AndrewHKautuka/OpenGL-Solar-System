#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Shader.hpp"

using namespace glm;

class ShaderProgram
{
public:
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	~ShaderProgram();
	
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, vec3 value) const;
	void setMat4(const std::string& name, mat4 value) const;
private:
	unsigned int ID;
	
	void checkProgramLinkErrors();
};