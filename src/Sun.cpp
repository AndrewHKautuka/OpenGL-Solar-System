#include "Sun.hpp"

const float Sun::RADIUS = 1.0f;
// Derived from real-life rotation period in days
const float Sun::INITIAL_SPIN_VELOCITY = 0.0394f;
const unsigned int Sun::STACK_COUNT = 36;
const char* Sun::TEXTURE_PATH = "textures/sunmap.jpg";

Sun::Sun(ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward) : Planet(RADIUS, STACK_COUNT, Texture(TEXTURE_PATH), pShader, pWorldUp, pForward)
{
	spinVelocity = INITIAL_SPIN_VELOCITY;
}