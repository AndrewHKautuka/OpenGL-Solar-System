#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const float MIN_PITCH = -89.0f, MAX_PITCH = 89.0f;

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 initialUp;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	
	glm::mat4 viewMatrix;
	
	float pitch;
	float yaw;
	
	const float minPitch, maxPitch;
public:
	Camera(glm::vec3 pPosition, glm::vec3 pWorldUp, glm::vec3 pForward, float pMinPitch, float pMaxPitch);
	Camera(glm::vec3 pPosition, glm::vec3 pWorldUp, glm::vec3 pForward);
	~Camera();
	
	void Move(glm::vec3 deltaMove);
	void AddDirectionOffest(float xOffset, float yOffset);
	
	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 pPosition);
	void SetForward(glm::vec3 pForward);
	glm::mat4 GetViewMatrix() const;
};