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
	float dMercury = rSun + 1.8f + rMercury;
	float dVenus = dMercury + rMercury + 1.8f + rVenus;
	float dEarth = dVenus + rVenus + 1.8f + rEarth;
	float dMoon = rEarth + 0.6f + rMoon;
	float dMars = dEarth + rEarth + 1.8f + rMars;
	
	// (Model) spin velocities
	float spinSpeedMultiplier = 10.0f;
	float sSun = 0.04f * spinSpeedMultiplier;
	float sMercury = 0.02f * spinSpeedMultiplier;
	float sVenus = 0.004f * spinSpeedMultiplier;
	float sEarth = 1.00f * spinSpeedMultiplier;
	float sMoon = 0.035f * spinSpeedMultiplier;
	float sMars = 0.95f * spinSpeedMultiplier;
	
	// (Model) orbit velocities
	float orbitSpeedMultiplier = 100.0f;
	float oMercury = 0.0115f * orbitSpeedMultiplier;
	float oVenus = 0.00445f * orbitSpeedMultiplier;
	float oEarth = 0.00275f * orbitSpeedMultiplier;
	float oMoon = 0.035f * spinSpeedMultiplier;
	float oMars = 0.00145f * orbitSpeedMultiplier;
	
	Planet sun(rSun, 18, sunTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	sun.SetSpinVelocity(sSun);
	unsigned int sunID = AddPlanet(sun);
	
	Planet mercury(rMercury, 18, mercuryTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	mercury.SetSpinVelocity(sMercury);
	mercury.SetOrbit(RetrievePlanet(sunID), dMercury, oMercury, 0.0f);
	AddPlanet(mercury);
	
	Planet venus(rVenus, 18, venusTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	venus.SetSpinVelocity(sVenus);
	venus.SetOrbit(RetrievePlanet(sunID), dVenus, oVenus, 0.0f);
	AddPlanet(venus);
	
	Planet earth(rEarth, 18, earthTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	earth.SetSpinVelocity(sEarth);
	earth.SetOrbit(RetrievePlanet(sunID), dEarth, oEarth, 0.0f);
	unsigned int earthID = AddPlanet(earth);
	
	Planet moon(rMoon, 18, moonTexture, moonShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	moon.SetSpinVelocity(sMoon);
	moon.SetOrbit(RetrievePlanet(earthID), dMoon, oMoon, 0.0f);
	unsigned int moonID = AddPlanet(moon);
	
	Planet mars(rMars, 18, marsTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	mars.SetSpinVelocity(sMars);
	mars.SetOrbit(RetrievePlanet(sunID), dMars, oMars, 0.0f);
	AddPlanet(mars);
	
	input->AddKeyStateAction(GLFW_KEY_W, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f,  *moveSpeed)); });
	input->AddKeyStateAction(GLFW_KEY_S, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f, -*moveSpeed)); });
	input->AddKeyStateAction(GLFW_KEY_A, PRESSED, [=](){ camera->Move(glm::vec3(-*moveSpeed, 0.0f,  0.0f)); });
	input->AddKeyStateAction(GLFW_KEY_D, PRESSED, [=](){ camera->Move(glm::vec3( *moveSpeed, 0.0f,  0.0f)); });
	
	input->AddKeyCommand(GLFW_KEY_LEFT, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* moon = RetrievePlanet(moonID);
		moon->SetOrbitVelocity(moon->GetOrbitVelocity() + 0.005f * orbitSpeedMultiplier);
	});
	input->AddKeyCommand(GLFW_KEY_RIGHT, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* moon = RetrievePlanet(moonID);
		moon->SetOrbitVelocity(moon->GetOrbitVelocity() - 0.005f * orbitSpeedMultiplier);
	});
	input->AddKeyCommand(GLFW_KEY_UP, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* sun = RetrievePlanet(sunID);
		sun->SetSpinVelocity(sun->GetSpinVelocity() + 0.05f * spinSpeedMultiplier);
	});
	input->AddKeyCommand(GLFW_KEY_DOWN, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* sun = RetrievePlanet(sunID);
		sun->SetSpinVelocity(sun->GetSpinVelocity() - 0.05f * spinSpeedMultiplier);
	});
	
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