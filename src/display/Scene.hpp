#pragma once

#include <vector>

#include "rendering/ShaderProgram.hpp"
#include "planet/Planet.hpp"

class Scene
{
private:
	ShaderProgram* shader;
	
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