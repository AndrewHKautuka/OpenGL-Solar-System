#include "Scene.hpp"

Scene::Scene()
{
	Shader vertex("shaders/planet.vs", VERTEX);
	Shader fragment("shaders/planet.fs", FRAGMENT);
	shader = new ShaderProgram(vertex, fragment);
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