#pragma once

#include <vector>

#include "rendering/Shader.hpp"
#include "planet/Planet.hpp"

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