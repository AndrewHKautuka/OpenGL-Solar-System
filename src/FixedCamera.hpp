#pragma once

#include "Camera.hpp"

class FixedCamera : public Camera
{
private:
	
public:
	FixedCamera(glm::vec3* pPosition, glm::vec3 pWorldUp, glm::vec3* pTarget);
	~FixedCamera();
	
	void AddDirectionOffest(float xOffset, float yOffset) override;
};
