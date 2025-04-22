#pragma once

#include <vector>

#include "ShaderProgram.hpp"
#include "Planet.hpp"

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