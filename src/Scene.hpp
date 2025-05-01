#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "InputHandler.hpp"
#include "Camera.hpp"
#include "ShaderPool.hpp"
#include "Planet.hpp"
#include "PointLightSource.hpp"
#include "DirectionalLightSource.hpp"

class Scene
{
private:
	float aspectRatio;
	ShaderPool shaderPool;
	Camera* camera;
	InputHandler* input;
	
	unsigned int maxPlanetsCount;
	unsigned int planetsCount = 0;
	Planet** planets;
	
	DirectionalLightSource* dirLightSource;
	PointLightSource* pointLightSource;
	
	glm::mat4 projection;
public:
	Scene(InputHandler* pInput);
	~Scene();
	
	unsigned int AddPlanet(const Planet& planet);
	Planet* RetrievePlanet(unsigned int id);
	
	void Initialize(float pAspectRatio);
	void SetAspectRatio(float pAspectRatio);
	
	void Update();
	void Render();
};