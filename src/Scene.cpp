#include "Scene.hpp"

Scene::Scene()
{
	shader = new Shader("shaders/shader.vs", "shaders/shader.fs");
	maxPlanetsCount = 6;
	planets = new Planet*[maxPlanetsCount];
}

Scene::~Scene()
{
	delete shader;
	shader = nullptr;
	
	delete [] planets;
	planets = nullptr;
}

void Scene::Initialize()
{
	shader->use();
}

void Scene::AddPlanet(Planet planet)
{
	planets[planetsCount] = new Planet(planet);
	planetsCount++;
}

void Scene::Render()
{
	shader->use();
	
	for (unsigned int i = 0; i < planetsCount; i++)
	{
		planets[i]->Draw();
	}
}