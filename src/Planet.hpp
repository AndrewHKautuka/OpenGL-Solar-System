#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "ShaderProgram.hpp"
#include "Sphere.h"
#include "Texture.hpp"

class Planet
{
public:
	Planet(float pRadius, glm::vec3 pPosition, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward);
	virtual ~Planet();
	
	void Update();
	void Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const;
	
	float GetSpinVelocity() const;
	void SetSpinVelocity(float pSpinVelocity);
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	
	// Speed of the planet's spin on its axis + its direction
	float spinVelocity = 0.0f;
	float spinAngle = 0.0f;
	
	ShaderProgram* shader;
	Sphere mesh;
	Texture texture;
	std::shared_ptr<glm::vec3> position;
	glm::mat4 modelMatrix;
};