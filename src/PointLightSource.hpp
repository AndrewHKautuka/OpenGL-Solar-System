#pragma once

#include "LightSource.hpp"
#include "Sphere.h"

class PointLightSource : public LightSource
{
public:
	PointLightSource(float pRadius, glm::vec3 pPosition, unsigned int pStackCount, ShaderProgram* pShader, glm::vec3 pLightColor);
	~PointLightSource();
	
	void Update() override;
	void Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const override;
	void ApplyToShader(ShaderProgram* const shader) override;
private:
	glm::vec3 lightVector;
	glm::vec3 position;
	glm::mat4 modelMatrix;
	Sphere mesh;
};