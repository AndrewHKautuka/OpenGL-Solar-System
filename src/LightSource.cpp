#include "LightSource.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

LightSource::LightSource(ShaderProgram* pShader, glm::vec3 pLightColor)
{
	shader = pShader;
	lightColor = pLightColor;
}

LightSource::~LightSource()
{
}

void LightSource::Update()
{
	
}

void LightSource::Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const
{
	shader->use();
	shader->setVec3("color", lightColor);
}

glm::vec3 LightSource::GetLightColor() const
{
	return lightColor;
}