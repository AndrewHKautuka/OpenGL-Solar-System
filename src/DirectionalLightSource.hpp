#pragma once

#include "LightSource.hpp"

class DirectionalLightSource : public LightSource
{
private:
	glm::vec3 lightVector;
public:
	DirectionalLightSource(ShaderProgram* pShader, glm::vec3 pLightColor, glm::vec3 pLightVector);
	~DirectionalLightSource();
	
	void Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const override;
	void ApplyToShader(ShaderProgram* const shader) override;
};