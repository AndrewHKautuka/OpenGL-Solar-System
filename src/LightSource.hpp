#pragma once

#include <glm/glm.hpp>

#include "Camera.hpp"
#include "ShaderProgram.hpp"

using namespace glm;

class LightSource
{
public:
	LightSource(ShaderProgram* pShader, vec3 pLightColor);
	~LightSource();
	
	virtual void Update();
	virtual void Draw(mat4* projectionMatrix, mat4* viewMatrix) const;
	
	vec3 GetLightColor() const;
	
	virtual void ApplyToShader(ShaderProgram* const shader) = 0;
protected:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	ShaderProgram* shader;
	vec3 lightColor;
};