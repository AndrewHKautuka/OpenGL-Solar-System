#include "DirectionalLightSource.hpp"

DirectionalLightSource::DirectionalLightSource(ShaderProgram* pShader, glm::vec3 pLightColor, glm::vec3 pLightVector) : LightSource(pShader, pLightColor)
{
	lightVector = pLightVector;
}

DirectionalLightSource::~DirectionalLightSource()
{
}

void DirectionalLightSource::Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const
{
	LightSource::Draw(projectionMatrix, viewMatrix);
}

void DirectionalLightSource::ApplyToShader(ShaderProgram* const shader)
{
	shader->setVec3("dirLightColor", lightColor);
	shader->setVec3("dirLightVector", lightVector);
}