#include "Scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "FreeCamera.hpp"

Scene::Scene(InputHandler* pInput)
{
	input = pInput;
	
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

float* moveSpeed = new float(0.5f);
float* rotSpeed = new float(1.0f);

void Scene::Initialize(float pAspectRatio)
{
	camera = new FreeCamera(new glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	Texture sunTexture("textures/sunmap.jpg");
	Texture mercuryTexture("textures/mercurymap.jpg");
	Texture venusTexture("textures/venusmap.jpg");
	Texture earthTexture("textures/earthmap1k.jpg");
	Texture moonTexture("textures/moonmap1k.jpg", GL_RED);
	Texture marsTexture("textures/marsmap1k.jpg");
	
	ShaderProgram* planetShader = shaderPool.RetrieveShaderProgram("planet");
	
	// (Model) radii of celestial bodies
	float rSun = 1.0f, rMercury = 0.2f, rVenus = 0.4f, rEarth = 0.5f, rMoon = 0.1f, rMars = 0.3f;
	
	Planet sun(rSun, 18, sunTexture, planetShader);
	Planet mercury(rMercury, 18, mercuryTexture, planetShader);
	Planet venus(rVenus, 18, venusTexture, planetShader);
	Planet earth(rEarth, 18, earthTexture, planetShader);
	Planet moon(rMoon, 18, moonTexture, planetShader);
	Planet mars(rMars, 18, marsTexture, planetShader);
	
	AddPlanet(sun);
	AddPlanet(mercury);
	AddPlanet(venus);
	AddPlanet(earth);
	AddPlanet(moon);
	AddPlanet(mars);
	
	input->AddStateAction(GLFW_KEY_W, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f,  *moveSpeed)); });
	input->AddStateAction(GLFW_KEY_S, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f, -*moveSpeed)); });
	input->AddStateAction(GLFW_KEY_A, PRESSED, [=](){ camera->Move(glm::vec3(-*moveSpeed, 0.0f,  0.0f)); });
	input->AddStateAction(GLFW_KEY_D, PRESSED, [=](){ camera->Move(glm::vec3( *moveSpeed, 0.0f,  0.0f)); });
	
	input->AddStateAction(GLFW_KEY_LEFT	, PRESSED, [=](){ camera->AddDirectionOffest( *rotSpeed, 0); });
	input->AddStateAction(GLFW_KEY_RIGHT, PRESSED, [=](){ camera->AddDirectionOffest(-*rotSpeed, 0); });
	input->AddStateAction(GLFW_KEY_UP	, PRESSED, [=](){ camera->AddDirectionOffest(0,  *rotSpeed); });
	input->AddStateAction(GLFW_KEY_DOWN	, PRESSED, [=](){ camera->AddDirectionOffest(0, -*rotSpeed); });
	
	SetAspectRatio(pAspectRatio);
	
	shaderPool.RetrieveShaderProgram("planet")->use();
	shaderPool.RetrieveShaderProgram("planet")->setMat4("projection", projection);
}

void Scene::SetAspectRatio(float pAspectRatio)
{
	aspectRatio = pAspectRatio;
	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Scene::AddPlanet(const Planet& planet)
{
	planets[planetsCount] = new Planet(planet);
	planetsCount++;
}

void Scene::Update()
{
	input->Update();
}

void Scene::Render()
{
	auto shader = shaderPool.RetrieveShaderProgram("planet");
	shader->use();
	shader->setMat4("view", camera->GetViewMatrix());
	
	for (unsigned int i = 0; i < planetsCount; i++)
	{
		planets[i]->Draw();
	}
}