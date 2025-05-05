#include "Moon.hpp"

const float Moon::RADIUS = 0.1f;
// Derived from real-life rotation period in days
const float Moon::INITIAL_SPIN_VELOCITY = 0.0366f;
// Derived from real-life orbit period in days
const float Moon::INITIAL_ORBIT_VELOCITY = 0.0366f;
const unsigned int Moon::STACK_COUNT = 36;
const char* Moon::TEXTURE_PATH = "textures/moonmap1k.jpg";

Moon::Moon(ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward) : Planet(RADIUS, STACK_COUNT, Texture(TEXTURE_PATH, GL_RED), pShader, pWorldUp, pForward)
{
	spinVelocity = INITIAL_SPIN_VELOCITY;
	orbitVelocity = INITIAL_ORBIT_VELOCITY;
}