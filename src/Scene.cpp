#include "Scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "FreeCamera.hpp"
#include "DirectionalLightSource.hpp"
#include "PointLightSource.hpp"

Scene::Scene(InputHandler* pInput)
{
	input = pInput;
	
	shaderPool.AddShader(new Shader("shaders/planet.vs", VERTEX), "planet.vs");
	shaderPool.AddShader(new Shader("shaders/planet.fs", FRAGMENT), "planet.fs");
	shaderPool.AddShader(new Shader("shaders/lightSource.vs", VERTEX), "lightSource.vs");
	shaderPool.AddShader(new Shader("shaders/lightSource.fs", FRAGMENT), "lightSource.fs");
	shaderPool.AddShader(new Shader("shaders/moon.fs", FRAGMENT), "moon.fs");
	
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("planet.fs")), "planet");
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("moon.fs")), "moon");
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("lightSource.vs"), *shaderPool.RetrieveShader("lightSource.fs")), "lightSource");
	
	shaderPool.ClearShaders();
	
	projection = glm::mat4(1.0f);
}

Scene::~Scene()
{
	shaderPool.ClearShaderPrograms();
}

float* moveSpeed = new float(0.1f);

void Scene::Initialize(float pAspectRatio)
{
	const glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
	camera = new FreeCamera(new glm::vec3(0.0f, 0.0f, -10.0f), worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	
	solarSystem.Initialize(&shaderPool, worldUp);
	
	input->AddKeyStateAction(GLFW_KEY_W, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f,  *moveSpeed)); });
	input->AddKeyStateAction(GLFW_KEY_S, PRESSED, [=](){ camera->Move(glm::vec3( 0.0f, 0.0f, -*moveSpeed)); });
	input->AddKeyStateAction(GLFW_KEY_A, PRESSED, [=](){ camera->Move(glm::vec3(-*moveSpeed, 0.0f,  0.0f)); });
	input->AddKeyStateAction(GLFW_KEY_D, PRESSED, [=](){ camera->Move(glm::vec3( *moveSpeed, 0.0f,  0.0f)); });
	
	input->AddKeyCommand(GLFW_KEY_LEFT, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* moon = solarSystem.GetMoon();
		moon->SetOrbitVelocity(moon->GetOrbitVelocity() + 0.005f);
	});
	input->AddKeyCommand(GLFW_KEY_RIGHT, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* moon = solarSystem.GetMoon();
		moon->SetOrbitVelocity(moon->GetOrbitVelocity() - 0.005f);
	});
	input->AddKeyCommand(GLFW_KEY_UP, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* sun = solarSystem.GetSun();
		sun->SetSpinVelocity(sun->GetSpinVelocity() + 0.05f);
	});
	input->AddKeyCommand(GLFW_KEY_DOWN, RELEASED, GLFW_MOD_NONE, [=](){
		Planet* sun = solarSystem.GetSun();
		sun->SetSpinVelocity(sun->GetSpinVelocity() - 0.05f);
	});
	
	const float mouseSensitivity = 0.1f;
	
	input->SetMouseMoveCommand([=](double xPos, double yPos){
		auto lastPos = input->GetLastMousePosition();
		camera->AddDirectionOffest(mouseSensitivity * (xPos - lastPos.first), mouseSensitivity * (yPos - lastPos.second));
	});
	
	SetAspectRatio(pAspectRatio);
	
	shaderPool.RetrieveShaderProgram("planet")->use();
	shaderPool.RetrieveShaderProgram("planet")->setMat4("projection", projection);
	
	dirLightSource = new DirectionalLightSource(shaderPool.RetrieveShaderProgram("lightSource"), glm::vec3(1.0f, 0.75f, 0.25f), glm::vec3(0.0f, 0.0f, -1.0f));
	pointLightSource = new PointLightSource(0.1f, glm::vec3(0.0f, 20.0f, 0.0f), 18, shaderPool.RetrieveShaderProgram("lightSource"), glm::vec3(0.1f, 0.25f, 1.0f));
}

void Scene::SetAspectRatio(float pAspectRatio)
{
	aspectRatio = pAspectRatio;
	projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Scene::Update()
{
	input->Update();
	
	dirLightSource->Update();
	pointLightSource->Update();
	solarSystem.Update();
}

void Scene::Render()
{
	glm::mat4 view = camera->GetViewMatrix();
	
	dirLightSource->Draw(&projection, &view);
	pointLightSource->Draw(&projection, &view);
	solarSystem.Render(&projection, camera, pointLightSource, dirLightSource);
}