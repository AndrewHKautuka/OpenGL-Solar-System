#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const float MIN_PITCH = -89.0f, MAX_PITCH = 89.0f;

class Camera
{
protected:
	glm::vec3* position;
	glm::vec3* target;
	glm::vec3 initialUp;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	
	glm::mat4 viewMatrix;
	
	float pitch;
	float yaw;
	
	const float minPitch, maxPitch;
public:
	Camera(glm::vec3* pPosition, glm::vec3 pWorldUp, float pMinPitch, float pMaxPitch);
	virtual ~Camera();
	
	void SetPosition(glm::vec3* pPosition);
	void SetTarget(glm::vec3* pTarget);
	virtual void AddDirectionOffest(float xOffset, float yOffset) = 0;
	
	glm::mat4 GetViewMatrix() const;
};