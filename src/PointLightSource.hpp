#pragma once

#include "LightSource.hpp"
#include "Sphere.h"

class PointLightSource : public LightSource
{
public:
	PointLightSource(float pRadius, vec3 pPosition, unsigned int pStackCount, ShaderProgram* pShader, vec3 pLightColor);
	~PointLightSource();
	
	void Update() override;
	void Draw(mat4* projectionMatrix, mat4* viewMatrix) const override;
	void ApplyToShader(ShaderProgram* const shader) override;
private:
	vec3 lightVector;
	vec3 position;
	mat4 modelMatrix;
	Sphere mesh;
};