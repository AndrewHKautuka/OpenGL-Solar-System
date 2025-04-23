#pragma once

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
public:
	Scene();
	~Scene();
	
	void AddPlanet(Planet planet);
	void Initialize();
	void Render();
};