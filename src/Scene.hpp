#pragma once

#include <vector>

#include "Shader.hpp"
#include "Planet.hpp"

class Scene
{
private:
	Shader* shader;
	
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