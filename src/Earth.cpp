#include "Earth.hpp"

const float Earth::RADIUS = 0.5f;
// Derived from real-life rotation period in days
const float Earth::INITIAL_SPIN_VELOCITY = 1.00f;
// Derived from real-life orbit period in days
const float Earth::INITIAL_ORBIT_VELOCITY = 0.00274f;
const unsigned int Earth::STACK_COUNT = 36;
const char* Earth::TEXTURE_PATH = "res/textures/earthmap1k.jpg";

Earth::Earth(ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward) : Planet(RADIUS, STACK_COUNT, Texture(TEXTURE_PATH), pShader, pWorldUp, pForward)
{
	spinVelocity = INITIAL_SPIN_VELOCITY;
	orbitVelocity = INITIAL_ORBIT_VELOCITY;
}