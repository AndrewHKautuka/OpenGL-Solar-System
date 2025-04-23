#include "FreeCamera.hpp"

FreeCamera::FreeCamera(glm::vec3* pPosition, glm::vec3 pCameraFront) : Camera(pPosition, MIN_PITCH, MAX_PITCH)
{
	cameraFront = pCameraFront;
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::AddDirectionOffest(float xOffset, float yOffset)
{
	yaw += xOffset;
	pitch += yOffset;
	
	glm::clamp(pitch, minPitch, maxPitch);
	
	glm::vec3 direction;
	direction.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	*target = *position + cameraFront;
}

void FreeCamera::SetCameraFront(glm::vec3 pCameraFront)
{
	cameraFront = pCameraFront;
}