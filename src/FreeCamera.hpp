#pragma once

#include "Camera.hpp"

class FreeCamera : public Camera
{
private:
	glm::vec3 cameraFront;
public:
	FreeCamera(glm::vec3* pPosition, glm::vec3 pCameraFront);
	~FreeCamera();
	
	void AddDirectionOffest(float xOffset, float yOffset) override;
	void SetCameraFront(glm::vec3 pCameraFront);
};
