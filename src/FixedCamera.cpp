#include "FixedCamera.hpp"

FixedCamera::FixedCamera(glm::vec3* pPosition, glm::vec3 pWorldUp, glm::vec3* pTarget) : Camera (pPosition, pWorldUp, MIN_PITCH, MAX_PITCH)
{
	target = pTarget;
}

FixedCamera::~FixedCamera()
{
}

void FixedCamera::AddDirectionOffest(float xOffset, float yOffset)
{
	
}