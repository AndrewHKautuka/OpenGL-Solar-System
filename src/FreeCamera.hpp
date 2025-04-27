#pragma once

#include "Camera.hpp"

class FreeCamera : public Camera
{
public:
	FreeCamera(glm::vec3* pPosition, glm::vec3 pWorldUp, glm::vec3 pForward);
	~FreeCamera();
	
	void AddDirectionOffest(float xOffset, float yOffset) override;
	void Move(glm::vec3 deltaMove) override;
};
