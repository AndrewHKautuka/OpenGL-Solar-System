#include "Planet.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "gLErrorHandle.hpp"

const float Planet::SPIN_SPEED_MULTIPLIER = 8.0f;
const float Planet::ORBIT_SPEED_MULTIPLIER = 80.0f;

Planet::Planet(float pRadius, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader, vec3 pWorldUp, vec3 pForward) : texture(pTexture), mesh(pRadius, pStackCount * 2, pStackCount, true, 2)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.getInterleavedVertexSize(), mesh.getInterleavedVertices(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexSize(), mesh.getIndices(), GL_STATIC_DRAW);
	
	unsigned int stride = mesh.getInterleavedStride();
	
	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) (0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	
	// Vertex Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// Texture Coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	shader = pShader;
	position = std::shared_ptr<vec3>(new vec3(0.0f, 0.0f, 0.0f));
	modelMatrix = mat4(1.0f);
	modelMatrix = translate(modelMatrix, *position);
	host = nullptr;
	
	forward = pForward;
	right = normalize(cross(forward, pWorldUp));
	up = cross(right, forward);
	
	color = vec3(1.0f, 1.0f, 1.0f);
}

Planet::~Planet()
{
	
}

void Planet::Update()
{
	spinAngle += fmod(spinVelocity * SPIN_SPEED_MULTIPLIER, 360.0f);
	orbitAngle += fmod(orbitVelocity * ORBIT_SPEED_MULTIPLIER, 360.0f);
	
	modelMatrix = mat4(1.0f);
	
	if (host != nullptr)
	{
		vec4 pos = rotate(mat4(1.0f), radians(orbitAngle), host->up) * vec4(0.0f, 0.0f, -orbitRadius, 1.0f);
		*position = vec3(pos.x, pos.y, pos.z) + *(host->position);
	}
	
	modelMatrix = translate(modelMatrix, *position);
	modelMatrix = rotate(modelMatrix, radians(spinAngle), up);
}

void Planet::Draw(mat4* projectionMatrix, Camera* camera, PointLightSource* pointLightSource, DirectionalLightSource* dirLightSource) const
{
	shader->use();
	shader->setVec3("objectColor", color);
	pointLightSource->ApplyToShader(shader);
	dirLightSource->ApplyToShader(shader);
	shader->setVec3("viewPos", camera->GetPosition());
	shader->setMat4("projection", *projectionMatrix);
	shader->setMat4("view", camera->GetViewMatrix());
	shader->setMat4("model", modelMatrix);
	
	glActiveTexture(GL_TEXTURE0);
	texture.BindTexture();
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, (void*) 0);
	glBindVertexArray(0);
}

void Planet::SetOrbit(Planet* pHost, float pOrbitRadius, float pOrbitAngle)
{
	host = pHost;
	orbitRadius = pOrbitRadius;
	orbitAngle = pOrbitAngle;
}

float Planet::GetOrbitVelocity() const
{
	return orbitVelocity;
}

void Planet::SetOrbitVelocity(float pOrbitVelocity)
{
	orbitVelocity = pOrbitVelocity;
}

float Planet::GetSpinVelocity() const
{
	return spinVelocity;
}

void Planet::SetSpinVelocity(float pSpinVelocity)
{
	spinVelocity = pSpinVelocity;
}