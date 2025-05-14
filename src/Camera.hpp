#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

static const float MIN_PITCH = -89.0f, MAX_PITCH = 89.0f;

class Camera
{
private:
	vec3 position;
	vec3 target;
	vec3 initialUp;
	vec3 forward;
	vec3 right;
	vec3 up;
	
	mat4 viewMatrix;
	
	float pitch;
	float yaw;
	
	const float minPitch, maxPitch;
public:
	Camera(vec3 pPosition, vec3 pWorldUp, vec3 pForward, float pMinPitch, float pMaxPitch);
	Camera(vec3 pPosition, vec3 pWorldUp, vec3 pForward);
	~Camera();
	
	void Move(vec3 deltaMove);
	void AddDirectionOffest(float xOffset, float yOffset);
	
	vec3 GetPosition() const;
	void SetPosition(vec3 pPosition);
	void SetForward(vec3 pForward);
	mat4 GetViewMatrix() const;
};