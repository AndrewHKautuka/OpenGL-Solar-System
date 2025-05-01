#pragma once

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "ShaderProgram.hpp"

class LightSource
{
public:
	LightSource(ShaderProgram* pShader, glm::vec3 pLightColor);
	~LightSource();
	
	virtual void Update();
	virtual void Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const;
	
	glm::vec3 GetLightColor() const;
	
	virtual void ApplyToShader(ShaderProgram* const shader) = 0;
protected:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	ShaderProgram* shader;
	glm::vec3 lightColor;
};