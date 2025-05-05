#pragma once

#include <glm/glm.hpp>

#include "Planet.hpp"
#include "Camera.hpp"
#include "PointLightSource.hpp"
#include "DirectionalLightSource.hpp"
#include "ShaderPool.hpp"

class SolarSystem
{
private:
	Planet* sun;
	Planet* mercury;
	Planet* venus;
	Planet* earth;
	Planet* moon;
	Planet* mars;
public:
	SolarSystem();
	~SolarSystem();
	
	void Initialize(const ShaderPool* shaderPool, const glm::vec3 worldUp);
	
	void Update();
	void Render(glm::mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource);
	
	Planet* GetSun() const;
	Planet* GetMercury() const;
	Planet* GetVenus() const;
	Planet* GetEarth() const;
	Planet* GetMoon() const;
	Planet* GetMars() const;
};