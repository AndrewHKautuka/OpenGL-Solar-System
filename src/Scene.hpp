#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "ShaderPool.hpp"
#include "Planet.hpp"

class Scene
{
private:
	ShaderPool shaderPool;
	
	unsigned int maxPlanetsCount;
	unsigned int planetsCount = 0;
	Planet** planets;
	
	glm::mat4 projection;
public:
	Scene();
	~Scene();
	
	void AddPlanet(Planet planet);
	void Initialize();
	void Render();
};