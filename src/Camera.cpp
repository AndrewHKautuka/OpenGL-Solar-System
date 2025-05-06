#include "Camera.hpp"

#include <iostream>

Camera::Camera(glm::vec3 pPosition, glm::vec3 pWorldUp, glm::vec3 pForward, float pMinPitch, float pMaxPitch) : minPitch(glm::max(pMinPitch, MIN_PITCH)), maxPitch(glm::min(pMaxPitch, MAX_PITCH)), position(pPosition), initialUp(pWorldUp), forward(pForward), right(glm::normalize(glm::cross(forward, initialUp))), up(glm::cross(right, forward))
{
	if (minPitch > maxPitch)
	{
		std::cout << "Minimum pitch is greater than maximum pitch (" << minPitch << " > " << maxPitch << ")\n";
		std::cout << "Undefined camera behaviour will occur" << std::endl;
	}
	target = position + forward;
}

Camera::Camera(glm::vec3 pPosition, glm::vec3 pWorldUp, glm::vec3 pForward) : Camera(pPosition, pWorldUp, pForward, MIN_PITCH, MAX_PITCH)
{}

Camera::~Camera()
{}

void Camera::Move(glm::vec3 deltaMove)
{
	position += deltaMove.z * forward;
	position += deltaMove.x * right;
	position += deltaMove.y * up;
	target = position + forward;
}

void Camera::AddDirectionOffest(float xOffset, float yOffset)
{
	yaw = fmod(yaw + xOffset, 360.0f);
	pitch = fmod(pitch + yOffset, 360.0f);
	
	pitch = glm::clamp(pitch, minPitch, maxPitch);
	
	glm::vec3 direction;
	direction.x = sin(glm::radians(-yaw)) * cos(glm::radians(-pitch));
	direction.y = sin(glm::radians(-pitch));
	direction.z = cos(glm::radians(-yaw)) * cos(glm::radians(-pitch));
	
	SetForward(glm::normalize(direction));
	right = glm::normalize(glm::cross(forward, initialUp));
	up = glm::cross(right, forward);
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::SetPosition(glm::vec3 pPosition)
{
	position = pPosition;
	target = position + forward;
}

void Camera::SetForward(glm::vec3 pForward)
{
	forward = pForward;
	target = position + forward;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(position, target, initialUp);
}