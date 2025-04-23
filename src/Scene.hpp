#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Camera.hpp"
#include "ShaderPool.hpp"
#include "Planet.hpp"

class Scene
{
private:
	float aspectRatio;
	ShaderPool shaderPool;
	Camera* camera;
	
	unsigned int maxPlanetsCount;
	unsigned int planetsCount = 0;
	Planet** planets;
	
	glm::mat4 projection;
public:
	Scene();
	~Scene();
	
	void AddPlanet(Planet planet);
	void Initialize(float pAspectRatio);
	void SetAspectRatio(float pAspectRatio);
	void Render();
};