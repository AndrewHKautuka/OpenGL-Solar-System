#pragma once

#include "Sphere.h"
#include "Texture.hpp"

class Planet
{
public:
	Planet(float pRadius, unsigned int pStackCount, Texture pTexture);
	virtual ~Planet();
	
	void Draw() const;
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	Sphere mesh;
	Texture texture;
};