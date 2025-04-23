#include "Scene.hpp"

Scene::Scene()
{
	Shader* vertex = new Shader("shaders/planet.vs", VERTEX);
	Shader* fragment = new Shader("shaders/planet.fs", FRAGMENT);
	
	shaderPool.AddShader(vertex, "planet.vs");
	shaderPool.AddShader(fragment, "planet.fs");
	
	ShaderProgram* shaderProgram = new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("planet.fs"));
	
	shaderPool.AddShaderProgram(shaderProgram, "planet");
	
	maxPlanetsCount = 6;
	planets = new Planet*[maxPlanetsCount];
}

Scene::~Scene()
{
	shaderPool.ClearShaders();
	shaderPool.ClearShaderPrograms();
	
	delete [] planets;
	planets = nullptr;
}

void Scene::Initialize()
{
	shaderPool.RetrieveShaderProgram("planet")->use();
}

void Scene::AddPlanet(Planet planet)
{
	planets[planetsCount] = new Planet(planet);
	planetsCount++;
}

void Scene::Render()
{
	shaderPool.RetrieveShaderProgram("planet")->use();
	
	for (unsigned int i = 0; i < planetsCount; i++)
	{
		planets[i]->Draw();
	}
}