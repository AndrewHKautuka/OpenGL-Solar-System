#include "Mercury.hpp"

const float Mercury::RADIUS = 0.2f;
// Derived from real-life rotation period in days
const float Mercury::INITIAL_SPIN_VELOCITY = 0.0171f;
// Derived from real-life orbit period in days
const float Mercury::INITIAL_ORBIT_VELOCITY = 0.0114f;
const unsigned int Mercury::STACK_COUNT = 36;
const char* Mercury::TEXTURE_PATH = "res/textures/mercurymap.jpg";

Mercury::Mercury(ShaderProgram* pShader, vec3 pWorldUp, vec3 pForward) : Planet(RADIUS, STACK_COUNT, Texture(TEXTURE_PATH), pShader, pWorldUp, pForward)
{
	spinVelocity = INITIAL_SPIN_VELOCITY;
	orbitVelocity = INITIAL_ORBIT_VELOCITY;
}