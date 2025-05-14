#include "Scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "DirectionalLightSource.hpp"
#include "PointLightSource.hpp"

Scene::Scene(InputListener* pInput)
{
	input = pInput;
	
	shaderPool.AddShader(new Shader("res/shaders/planet.vs", VERTEX), "planet.vs");
	shaderPool.AddShader(new Shader("res/shaders/planet.fs", FRAGMENT), "planet.fs");
	shaderPool.AddShader(new Shader("res/shaders/lightSource.vs", VERTEX), "lightSource.vs");
	shaderPool.AddShader(new Shader("res/shaders/lightSource.fs", FRAGMENT), "lightSource.fs");
	shaderPool.AddShader(new Shader("res/shaders/moon.fs", FRAGMENT), "moon.fs");
	
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("planet.fs")), "planet");
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("planet.vs"), *shaderPool.RetrieveShader("moon.fs")), "moon");
	shaderPool.AddShaderProgram(new ShaderProgram(*shaderPool.RetrieveShader("lightSource.vs"), *shaderPool.RetrieveShader("lightSource.fs")), "lightSource");
	
	shaderPool.ClearShaders();
	
	projection = mat4(1.0f);
}

Scene::~Scene()
{
	shaderPool.ClearShaderPrograms();
}

float* moveSpeed = new float(0.1f);

void Scene::Initialize(float pAspectRatio)
{
	const vec3 worldUp(0.0f, 1.0f, 0.0f);
	camera = new Camera(vec3(0.0f, 0.0f, -10.0f), worldUp, vec3(0.0f, 0.0f, 1.0f));
	
	solarSystem.Initialize(&shaderPool, worldUp);
	
	InputBinding& binding = input->GetInputBinding();
	
	binding.AddKeyStateAction("camera.move.forward", [=](){ camera->Move(vec3( 0.0f, 0.0f,  *moveSpeed)); });
	binding.AddKeyStateAction("camera.move.backward", [=](){ camera->Move(vec3( 0.0f, 0.0f, -*moveSpeed)); });
	binding.AddKeyStateAction("camera.move.left", [=](){ camera->Move(vec3(-*moveSpeed, 0.0f,  0.0f)); });
	binding.AddKeyStateAction("camera.move.right", [=](){ camera->Move(vec3( *moveSpeed, 0.0f,  0.0f)); });
	
	binding.AddKeyCommand("moon.orbit.speed_up", [=](){
		Planet* moon = solarSystem.GetMoon();
		moon->SetOrbitVelocity(moon->GetOrbitVelocity() + 0.005f);
	});
	binding.AddKeyCommand("moon.orbit.speed_down", [=](){
		Planet* moon = solarSystem.GetMoon();
		moon->SetOrbitVelocity(moon->GetOrbitVelocity() - 0.005f);
	});
	binding.AddKeyCommand("sun.spin.speed_up", [=](){
		Planet* sun = solarSystem.GetSun();
		sun->SetSpinVelocity(sun->GetSpinVelocity() + 0.05f);
	});
	binding.AddKeyCommand("sun.spin.speed_down", [=](){
		Planet* sun = solarSystem.GetSun();
		sun->SetSpinVelocity(sun->GetSpinVelocity() - 0.05f);
	});
	
	const float mouseSensitivity = 0.1f;
	
	binding.SetMouseMoveCommand([=, &binding](double xPos, double yPos){
		auto lastPos = binding.GetLastMousePosition();
		camera->AddDirectionOffest(mouseSensitivity * (xPos - lastPos.first), mouseSensitivity * (yPos - lastPos.second));
	});
	
	SetAspectRatio(pAspectRatio);
	
	shaderPool.RetrieveShaderProgram("planet")->use();
	shaderPool.RetrieveShaderProgram("planet")->setMat4("projection", projection);
	
	dirLightSource = new DirectionalLightSource(shaderPool.RetrieveShaderProgram("lightSource"), vec3(1.0f, 0.75f, 0.25f), vec3(0.0f, 0.0f, -1.0f));
	pointLightSource = new PointLightSource(0.1f, vec3(0.0f, 20.0f, 0.0f), 18, shaderPool.RetrieveShaderProgram("lightSource"), vec3(0.1f, 0.25f, 1.0f));
}

void Scene::SetAspectRatio(float pAspectRatio)
{
	aspectRatio = pAspectRatio;
	projection = perspective(radians(45.0f), aspectRatio, 0.1f, 100.0f);
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
	mat4 view = camera->GetViewMatrix();
	
	dirLightSource->Draw(&projection, &view);
	pointLightSource->Draw(&projection, &view);
	solarSystem.Render(&projection, camera, pointLightSource, dirLightSource);
}