#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "InputHandler.hpp"
#include "Camera.hpp"
#include "ShaderPool.hpp"
#include "SolarSystem.hpp"
#include "PointLightSource.hpp"
#include "DirectionalLightSource.hpp"

class Scene
{
private:
	float aspectRatio;
	ShaderPool shaderPool;
	Camera* camera;
	InputHandler* input;
	
	SolarSystem solarSystem;
	
	DirectionalLightSource* dirLightSource;
	PointLightSource* pointLightSource;
	
	glm::mat4 projection;
public:
	Scene(InputHandler* pInput);
	~Scene();
	
	void Initialize(float pAspectRatio);
	void SetAspectRatio(float pAspectRatio);
	
	void Update();
	void Render();
};