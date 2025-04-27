#include "Camera.hpp"

#include <iostream>

Camera::Camera(glm::vec3* pPosition, glm::vec3 pWorldUp, float pMinPitch, float pMaxPitch) : position(pPosition), minPitch(glm::max(pMinPitch, MIN_PITCH)), maxPitch(glm::min(pMaxPitch, MAX_PITCH))
{
	if (minPitch > maxPitch)
	{
		std::cout << "Minimum pitch is greater than maximum pitch (" << minPitch << " > " << maxPitch << ")\n";
		std::cout << "Undefined camera behaviour will occur" << std::endl;
	}
	
	initialUp = pWorldUp;
}

Camera::~Camera()
{
	if (position != nullptr)
	{
		delete position;
		position = nullptr;
	}
	if (target != nullptr)
	{
		delete target;
		target = nullptr;
	}
}

void Camera::SetPosition(glm::vec3* pPosition)
{
	position = pPosition;
}

void Camera::SetTarget(glm::vec3* pTarget)
{
	target = pTarget;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(*position, *target, initialUp);
}