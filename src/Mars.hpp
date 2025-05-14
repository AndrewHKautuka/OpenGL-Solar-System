#pragma once

#include "Planet.hpp"

class Mars : public Planet
{
public:
	static const float RADIUS;
	static const float INITIAL_SPIN_VELOCITY;
	static const float INITIAL_ORBIT_VELOCITY;
	static const unsigned int STACK_COUNT;
	static const char* TEXTURE_PATH;
	
	Mars(ShaderProgram* pShader, vec3 pWorldUp, vec3 pForward);
};