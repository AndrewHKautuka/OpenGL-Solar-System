#include "Venus.hpp"

const float Venus::RADIUS = 0.4f;
// Derived from real-life rotation period in days
const float Venus::INITIAL_SPIN_VELOCITY = 0.00411f;
// Derived from real-life orbit period in days
const float Venus::INITIAL_ORBIT_VELOCITY = 0.00445;
const unsigned int Venus::STACK_COUNT = 36;
const char* Venus::TEXTURE_PATH = "res/textures/venusmap.jpg";

Venus::Venus(ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward) : Planet(RADIUS, STACK_COUNT, Texture(TEXTURE_PATH), pShader, pWorldUp, pForward)
{
	spinVelocity = INITIAL_SPIN_VELOCITY;
	orbitVelocity = INITIAL_ORBIT_VELOCITY;
}