#include "DirectionalLightSource.hpp"

DirectionalLightSource::DirectionalLightSource(ShaderProgram* pShader, vec3 pLightColor, vec3 pLightVector) : LightSource(pShader, pLightColor)
{
	lightVector = pLightVector;
}

DirectionalLightSource::~DirectionalLightSource()
{
}

void DirectionalLightSource::Draw(mat4* projectionMatrix, mat4* viewMatrix) const
{
	LightSource::Draw(projectionMatrix, viewMatrix);
}

void DirectionalLightSource::ApplyToShader(ShaderProgram* const shader)
{
	shader->setVec3("dirLightColor", lightColor);
	shader->setVec3("dirLightVector", lightVector);
}