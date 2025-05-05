#include "SolarSystem.hpp"

SolarSystem::SolarSystem()
{
	
}

SolarSystem::~SolarSystem()
{
	
}

void SolarSystem::Initialize(const ShaderPool* shaderPool, const glm::vec3 worldUp)
{
	Texture sunTexture("textures/sunmap.jpg");
	Texture mercuryTexture("textures/mercurymap.jpg");
	Texture venusTexture("textures/venusmap.jpg");
	Texture earthTexture("textures/earthmap1k.jpg");
	Texture moonTexture("textures/moonmap1k.jpg", GL_RED);
	Texture marsTexture("textures/marsmap1k.jpg");
	
	ShaderProgram* planetShader = shaderPool->RetrieveShaderProgram("planet");
	ShaderProgram* moonShader = shaderPool->RetrieveShaderProgram("moon");
	
	// (Model) radii of celestial bodies
	float rSun = 1.0f, rMercury = 0.2f, rVenus = 0.4f, rEarth = 0.5f, rMoon = 0.1f, rMars = 0.3f;
	
	// (Model) distances between celestial body and sun
	float dMercury = rSun + 1.8f + rMercury;
	float dVenus = dMercury + rMercury + 1.8f + rVenus;
	float dEarth = dVenus + rVenus + 1.8f + rEarth;
	float dMoon = rEarth + 0.6f + rMoon;
	float dMars = dEarth + rEarth + 1.8f + rMars;
	
	// (Model) spin velocities
	float sSun = 0.4f;
	float sMercury = 0.2f;
	float sVenus = 0.04f;
	float sEarth = 1.00f;
	float sMoon = 0.035f;
	float sMars = 0.95f;
	
	// (Model) orbit velocities
	float oMercury = 0.0115f;
	float oVenus = 0.00445f;
	float oEarth = 0.00275f;
	float oMoon = 0.035f;
	float oMars = 0.00145f;
	
	sun = new Planet(rSun, 36, sunTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	sun->SetSpinVelocity(sSun);
	
	mercury = new Planet(rMercury, 36, mercuryTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	mercury->SetSpinVelocity(sMercury);
	mercury->SetOrbit(sun, dMercury, oMercury, 0.0f);
	
	venus = new Planet(rVenus, 36, venusTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	venus->SetSpinVelocity(sVenus);
	venus->SetOrbit(sun, dVenus, oVenus, 0.0f);
	
	earth = new Planet(rEarth, 36, earthTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	earth->SetSpinVelocity(sEarth);
	earth->SetOrbit(sun, dEarth, oEarth, 0.0f);
	
	moon = new Planet(rMoon, 36, moonTexture, moonShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	moon->SetSpinVelocity(sMoon);
	moon->SetOrbit(earth, dMoon, oMoon, 0.0f);
	
	mars = new Planet(rMars, 36, marsTexture, planetShader, worldUp, glm::vec3(0.0f, 0.0f, 1.0f));
	mars->SetSpinVelocity(sMars);
	mars->SetOrbit(sun, dMars, oMars, 0.0f);
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

void SolarSystem::Render(glm::mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource)
{
	sun->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	mercury->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	venus->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	earth->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	moon->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
	mars->Draw(projectionMatrix, camera, pointLightSource, dirLightSource);
}

Planet* SolarSystem::GetSun() const
{
	return sun;
}

Planet* SolarSystem::GetMercury() const
{
	return mercury;
}

Planet* SolarSystem::GetVenus() const
{
	return venus;
}

Planet* SolarSystem::GetEarth() const
{
	return earth;
}

Planet* SolarSystem::GetMoon() const
{
	return moon;
}

Planet* SolarSystem::GetMars() const
{
	return mars;
}