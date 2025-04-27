#pragma once

#include <glm/glm.hpp>

#include "ShaderProgram.hpp"
#include "Sphere.h"
#include "Texture.hpp"

class Planet
{
public:
	Planet(float pRadius, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader);
	virtual ~Planet();
	
	void Update();
	void Draw() const;
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	ShaderProgram* shader;
	Sphere mesh;
	Texture texture;
	glm::mat4 modelMatrix;
};