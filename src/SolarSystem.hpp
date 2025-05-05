#pragma once

#include <glm/glm.hpp>

#include "Planet.hpp"
#include "Sun.hpp"
#include "Mercury.hpp"
#include "Venus.hpp"
#include "Earth.hpp"
#include "Moon.hpp"
#include "Mars.hpp"
#include "Camera.hpp"
#include "PointLightSource.hpp"
#include "DirectionalLightSource.hpp"
#include "ShaderPool.hpp"

class SolarSystem
{
private:
	Sun* sun;
	Mercury* mercury;
	Venus* venus;
	Earth* earth;
	Moon* moon;
	Mars* mars;
public:
	SolarSystem();
	~SolarSystem();
	
	void Initialize(const ShaderPool* shaderPool, const glm::vec3 worldUp);
	
	void Update();
	void Render(glm::mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource);
	
	Sun* GetSun() const;
	Mercury* GetMercury() const;
	Venus* GetVenus() const;
	Earth* GetEarth() const;
	Moon* GetMoon() const;
	Mars* GetMars() const;
};