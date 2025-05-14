#pragma once

#include "LightSource.hpp"

class DirectionalLightSource : public LightSource
{
private:
	vec3 lightVector;
public:
	DirectionalLightSource(ShaderProgram* pShader, vec3 pLightColor, vec3 pLightVector);
	~DirectionalLightSource();
	
	void Draw(mat4* projectionMatrix, mat4* viewMatrix) const override;
	void ApplyToShader(ShaderProgram* const shader) override;
};