#include "Scene.hpp"

Scene::Scene()
{
	
	shaderPool.AddShader(new Shader("shaders/planet.vs", VERTEX), "planet.vs");
	shaderPool.AddShader(new Shader("shaders/planet.fs", FRAGMENT), "planet.fs");
	
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("planet.fs")), "planet");
	
	maxPlanetsCount = 6;
	planets = new Planet*[maxPlanetsCount];
	
	projection = glm::mat4(1.0f);
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
	shaderPool.RetrieveShaderProgram("planet")->setMat4("projection", projection);
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