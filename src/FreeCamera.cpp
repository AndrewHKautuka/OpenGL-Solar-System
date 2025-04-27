#include "FreeCamera.hpp"

FreeCamera::FreeCamera(glm::vec3* pPosition, glm::vec3 pWorldUp, glm::vec3 pForward) : Camera(pPosition, pWorldUp, MIN_PITCH, MAX_PITCH)
{
	forward = pForward;
	target = new glm::vec3(*position + forward);
	right = glm::normalize(glm::cross(forward, initialUp));
	up = glm::cross(right, forward);
}

FreeCamera::~FreeCamera()
{
	delete target;
}

void FreeCamera::AddDirectionOffest(float xOffset, float yOffset)
{
	yaw = fmod(yaw + xOffset, 360.0f);
	pitch = fmod(pitch + yOffset, 360.0f);
	
	glm::clamp(pitch, minPitch, maxPitch);
	
	glm::vec3 direction;
	direction.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	forward = glm::normalize(direction);
	right = glm::normalize(glm::cross(forward, initialUp));
	up = glm::cross(right, forward);
	
	*target = *position + forward;
}

void FreeCamera::Move(glm::vec3 deltaMove)
{
	Camera::Move(deltaMove);
	*target = *position + forward;
}