#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "ShaderProgram.hpp"
#include "Sphere.h"
#include "Texture.hpp"
#include "Camera.hpp"
#include "PointLightSource.hpp"
#include "DirectionalLightSource.hpp"

class Planet
{
public:
	static const float SPIN_SPEED_MULTIPLIER;
	static const float ORBIT_SPEED_MULTIPLIER;
	
	Planet(float pRadius, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward);
	virtual ~Planet();
	
	void Update();
	void Draw(glm::mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource) const;
	
	void SetOrbit(Planet* pHost, float pOrbitRadius, float pOrbitVelocity, float pOrbitAngle);
	float GetOrbitVelocity() const;
	void SetOrbitVelocity(float pOrbitVelocity);
	
	float GetSpinVelocity() const;
	void SetSpinVelocity(float pSpinVelocity);
protected:
	glm::vec3 color;
	
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
	
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	
	ShaderProgram* shader;
	Sphere mesh;
	Texture texture;
	std::shared_ptr<glm::vec3> position;
	glm::mat4 modelMatrix;
};