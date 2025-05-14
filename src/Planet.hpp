#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "ShaderProgram.hpp"
#include "Sphere.h"
#include "Texture.hpp"
#include "Camera.hpp"
#include "PointLightSource.hpp"
#include "DirectionalLightSource.hpp"

using namespace glm;

class Planet
{
public:
	static const float SPIN_SPEED_MULTIPLIER;
	static const float ORBIT_SPEED_MULTIPLIER;
	
	Planet(float pRadius, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader, vec3 pWorldUp, vec3 pForward);
	virtual ~Planet();
	
	void Update();
	void Draw(mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource) const;
	
	void SetOrbit(Planet* pHost, float pOrbitRadius, float pOrbitAngle);
	float GetOrbitVelocity() const;
	void SetOrbitVelocity(float pOrbitVelocity);
	
	float GetSpinVelocity() const;
	void SetSpinVelocity(float pSpinVelocity);
protected:
	vec3 color;
	
	// Speed of the planet's spin on its axis + its direction
	float spinVelocity = 0.0f;
	float spinAngle = 0.0f;
	
	Planet* host;
	float orbitRadius = 0.0f;
	float orbitVelocity = 0.0f;
	float orbitAngle = 0.0f;
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	vec3 forward;
	vec3 right;
	vec3 up;
	
	ShaderProgram* shader;
	Sphere mesh;
	Texture texture;
	std::shared_ptr<vec3> position;
	mat4 modelMatrix;
};