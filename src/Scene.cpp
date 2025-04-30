#include "Scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "FreeCamera.hpp"

Scene::Scene(InputHandler* pInput)
{
	input = pInput;
	
	shaderPool.AddShader(new Shader("shaders/planet.vs", VERTEX), "planet.vs");
	shaderPool.AddShader(new Shader("shaders/planet.fs", FRAGMENT), "planet.fs");
	shaderPool.AddShader(new Shader("shaders/moon.fs", FRAGMENT), "moon.fs");
	
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("planet.fs")), "planet");
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("moon.fs")), "moon");
	
	shaderPool.ClearShaders();
	
	maxPlanetsCount = 6;
	planets = new Planet*[maxPlanetsCount];
	
	projection = glm::mat4(1.0f);
}

Scene::~Scene()
{
	shaderPool.ClearShaderPrograms();
	
	delete [] planets;
	planets = nullptr;
}

float* moveSpeed = new float(0.1f);

void Scene::Initialize(float pAspectRatio)
{
	glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
	camera = new FreeCamera(new glm::vec3(0.0f, 0.0f, -10.0f), worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	
	Texture sunTexture("textures/sunmap.jpg");
	Texture mercuryTexture("textures/mercurymap.jpg");
	Texture venusTexture("textures/venusmap.jpg");
	Texture earthTexture("textures/earthmap1k.jpg");
	Texture moonTexture("textures/moonmap1k.jpg", GL_RED);
	Texture marsTexture("textures/marsmap1k.jpg");
	
	ShaderProgram* planetShader = shaderPool.RetrieveShaderProgram("planet");
	ShaderProgram* moonShader = shaderPool.RetrieveShaderProgram("moon");
	
	// (Model) radii of celestial bodies
	float rSun = 1.0f, rMercury = 0.2f, rVenus = 0.4f, rEarth = 0.5f, rMoon = 0.1f, rMars = 0.3f;
	
	// (Model) distances between celestial body and sun
	float dMercury = rSun + 0.4f + rMercury;
	float dVenus = dMercury + rMercury + 0.4f + rVenus;
	float dEarth = dVenus + rVenus + 0.4f + rEarth;
	float dMoon = dEarth + rEarth + 0.2f + rMoon;
	float dMars = dEarth + rEarth + 0.4f + rMars;
	
	Planet sun(rSun, glm::vec3(0.0f, 0.0f, 0.0f), 18, sunTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	Planet mercury(rMercury, glm::vec3(-dMercury, 0.0f, 0.0f), 18, mercuryTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	Planet venus(rVenus, glm::vec3(dVenus, 0.0f, 0.0f), 18, venusTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	Planet earth(rEarth, glm::vec3(-dEarth, 0.0f, 0.0f), 18, earthTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	Planet moon(rMoon, glm::vec3(-dMoon, 0.0f, 0.0f), 18, moonTexture, moonShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	Planet mars(rMars, glm::vec3(dMars, 0.0f, 0.0f), 18, marsTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	
	// Set Spin Velocities
	float sSun = 0.4f, sMercury = 0.2f, sVenus = 0.04f, sEarth = 10.0f, sMoon = 0.35f, sMars = 9.5f;
	
	sun.SetSpinVelocity(sSun);
	mercury.SetSpinVelocity(sMercury);
	venus.SetSpinVelocity(sVenus);
	earth.SetSpinVelocity(sEarth);
	moon.SetSpinVelocity(sMoon);
	mars.SetSpinVelocity(sMars);
	
	AddPlanet(sun);
	AddPlanet(mercury);
	AddPlanet(venus);
	AddPlanet(earth);
	AddPlanet(moon);
	AddPlanet(mars);
	
	input->AddKeyStateAction(GLFW_KEY_W, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f,  *moveSpeed)); });
	input->AddKeyStateAction(GLFW_KEY_S, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f, -*moveSpeed)); });
	input->AddKeyStateAction(GLFW_KEY_A, PRESSED, [=](){ camera->Move(glm::vec3(-*moveSpeed, 0.0f,  0.0f)); });
	input->AddKeyStateAction(GLFW_KEY_D, PRESSED, [=](){ camera->Move(glm::vec3( *moveSpeed, 0.0f,  0.0f)); });
	
	const float mouseSensitivity = 0.1f;
	
	input->SetMouseMoveCommand([=](double xPos, double yPos){
		auto lastPos = input->GetLastMousePosition();
		camera->AddDirectionOffest(mouseSensitivity * (xPos - lastPos.first), mouseSensitivity * (yPos - lastPos.second));
	});
	
	SetAspectRatio(pAspectRatio);
	
	shaderPool.RetrieveShaderProgram("planet")->use();
	shaderPool.RetrieveShaderProgram("planet")->setMat4("projection", projection);
}

void Scene::SetAspectRatio(float pAspectRatio)
{
	aspectRatio = pAspectRatio;
	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

unsigned int Scene::AddPlanet(const Planet& planet)
{
	planets[planetsCount] = new Planet(planet);
	planetsCount++;
	return planetsCount - 1;
}

Planet* Scene::RetrievePlanet(unsigned int id)
{
	if (id >= planetsCount || id < 0)
	{
		return nullptr;
	}
	
	return planets[id];
}

void Scene::Update()
{
	input->Update();
	
	for (unsigned int i = 0; i < planetsCount; i++)
	{
		planets[i]->Update();
	}
}

void Scene::Render()
{
	glm::mat4 view = camera->GetViewMatrix();
	
	for (unsigned int i = 0; i < planetsCount; i++)
	{
		planets[i]->Draw(&projection, &view);
	}
}