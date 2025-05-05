#pragma once

#include "Planet.hpp"

class Moon : public Planet
{
public:
	static const float RADIUS;
	static const float INITIAL_SPIN_VELOCITY;
	static const float INITIAL_ORBIT_VELOCITY;
	static const unsigned int STACK_COUNT;
	static const char* TEXTURE_PATH;
	
	Moon(ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward);
};