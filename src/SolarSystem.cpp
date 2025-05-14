#include "SolarSystem.hpp"

SolarSystem::SolarSystem()
{
	
}

SolarSystem::~SolarSystem()
{
	delete sun;
	sun = nullptr;
	
	delete mercury;
	mercury = nullptr;
	
	delete venus;
	venus = nullptr;
	
	delete earth;
	earth = nullptr;
	
	delete moon;
	moon = nullptr;
	
	delete mars;
	mars = nullptr;
}

void SolarSystem::Initialize(const ShaderPool* shaderPool, const vec3 worldUp)
{
	ShaderProgram* planetShader = shaderPool->RetrieveShaderProgram("planet");
	ShaderProgram* moonShader = shaderPool->RetrieveShaderProgram("moon");
	
	// (Model) distances between celestial body and sun
	float dMercury = Sun::RADIUS + 1.8f + Mercury::RADIUS;
	float dVenus = dMercury + Mercury::RADIUS + 1.8f + Venus::RADIUS;
	float dEarth = dVenus + Venus::RADIUS + 1.8f + Earth::RADIUS;
	float dMoon = Earth::RADIUS + 0.6f + Moon::RADIUS;
	float dMars = dEarth + Earth::RADIUS + 1.8f + Mars::RADIUS;
	
	sun = new Sun(planetShader, worldUp, vec3(0.0f, 0.0f, 1.0f));
	
	mercury = new Mercury(planetShader, worldUp, vec3(0.0f, 0.0f, 1.0f));
	mercury->SetOrbit(sun, dMercury, 0.0f);
	
	venus = new Venus(planetShader, worldUp, vec3(0.0f, 0.0f, 1.0f));
	venus->SetOrbit(sun, dVenus, 0.0f);
	
	earth = new Earth(planetShader, worldUp, vec3(0.0f, 0.0f, 1.0f));
	earth->SetOrbit(sun, dEarth, 0.0f);
	
	moon = new Moon(moonShader, worldUp, vec3(0.0f, 0.0f, 1.0f));
	moon->SetOrbit(earth, dMoon, 0.0f);
	
	mars = new Mars(planetShader, worldUp, vec3(0.0f, 0.0f, 1.0f));
	mars->SetOrbit(sun, dMars, 0.0f);
}

void SolarSystem::Update()
{
	sun->Update();
	mercury->Update();
	venus->Update();
	earth->Update();
	moon->Update();
	mars->Update();
}

void SolarSystem::Render(mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource)
{
	sun->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	mercury->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	venus->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	earth->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	moon->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	mars->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
}

Sun* SolarSystem::GetSun() const
{
	return sun;
}

Mercury* SolarSystem::GetMercury() const
{
	return mercury;
}

Venus* SolarSystem::GetVenus() const
{
	return venus;
}

Earth* SolarSystem::GetEarth() const
{
	return earth;
}

Moon* SolarSystem::GetMoon() const
{
	return moon;
}

Mars* SolarSystem::GetMars() const
{
	return mars;
}