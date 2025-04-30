#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "ShaderProgram.hpp"
#include "Sphere.h"
#include "Texture.hpp"

class Planet
{
public:
	Planet(float pRadius, glm::vec3 pPosition, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader);
	virtual ~Planet();
	
	void Update();
	void Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const;
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	ShaderProgram* shader;
	Sphere mesh;
	Texture texture;
	std::shared_ptr<glm::vec3> position;
	glm::mat4 modelMatrix;
};