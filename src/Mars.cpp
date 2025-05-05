#include "Mars.hpp"

const float Mars::RADIUS = 0.3f;
// Derived from real-life rotation period in days
const float Mars::INITIAL_SPIN_VELOCITY = 0.971f;
// Derived from real-life orbit period in days
const float Mars::INITIAL_ORBIT_VELOCITY = 0.00146f;
const unsigned int Mars::STACK_COUNT = 36;
const char* Mars::TEXTURE_PATH = "textures/marsmap1k.jpg";

Mars::Mars(ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward) : Planet(RADIUS, STACK_COUNT, Texture(TEXTURE_PATH), pShader, pWorldUp, pForward)
{
	spinVelocity = INITIAL_SPIN_VELOCITY;
	orbitVelocity = INITIAL_ORBIT_VELOCITY;
}