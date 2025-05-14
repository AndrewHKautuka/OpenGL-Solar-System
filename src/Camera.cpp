#include "Camera.hpp"

#include <iostream>

Camera::Camera(vec3 pPosition, vec3 pWorldUp, vec3 pForward, float pMinPitch, float pMaxPitch) : minPitch(max(pMinPitch, MIN_PITCH)), maxPitch(min(pMaxPitch, MAX_PITCH)), position(pPosition), initialUp(pWorldUp), forward(pForward), right(normalize(cross(forward, initialUp))), up(cross(right, forward))
{
	if (minPitch > maxPitch)
	{
		std::cout << "Minimum pitch is greater than maximum pitch (" << minPitch << " > " << maxPitch << ")\n";
		std::cout << "Undefined camera behaviour will occur" << std::endl;
	}
	target = position + forward;
}

Camera::Camera(vec3 pPosition, vec3 pWorldUp, vec3 pForward) : Camera(pPosition, pWorldUp, pForward, MIN_PITCH, MAX_PITCH)
{}

Camera::~Camera()
{}

void Camera::Move(vec3 deltaMove)
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
	
	pitch = clamp(pitch, minPitch, maxPitch);
	
	vec3 direction;
	direction.x = sin(radians(-yaw)) * cos(radians(-pitch));
	direction.y = sin(radians(-pitch));
	direction.z = cos(radians(-yaw)) * cos(radians(-pitch));
	
	SetForward(normalize(direction));
	right = normalize(cross(forward, initialUp));
	up = cross(right, forward);
}

vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::SetPosition(vec3 pPosition)
{
	position = pPosition;
	target = position + forward;
}

void Camera::SetForward(vec3 pForward)
{
	forward = pForward;
	target = position + forward;
}

mat4 Camera::GetViewMatrix() const
{
	return lookAt(position, target, initialUp);
}