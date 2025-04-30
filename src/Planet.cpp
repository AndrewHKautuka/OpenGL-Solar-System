#include "Planet.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "gLErrorHandle.hpp"

Planet::Planet(float pRadius, glm::vec3 pPosition, unsigned int pStackCount, Texture pTexture, ShaderProgram* pShader, glm::vec3 pWorldUp, glm::vec3 pForward) : texture(pTexture), mesh(Sphere(pRadius, pStackCount * 2, pStackCount, true, 2))
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
	position = std::shared_ptr<glm::vec3>(new glm::vec3(pPosition));
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, *position);
	
	forward = pForward;
	right = glm::normalize(glm::cross(forward, pWorldUp));
	up = glm::cross(right, forward);
}

Planet::~Planet()
{
	
}

void Planet::Update()
{
	spinAngle += fmod(spinVelocity, 360.0f);
	
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, *position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(spinAngle), up);
}

void Planet::Draw(glm::mat4* projectionMatrix, glm::mat4* viewMatrix) const
{
	shader->use();
	shader->setMat4("projection", *projectionMatrix);
	shader->setMat4("view", *viewMatrix);
	shader->setMat4("model", modelMatrix);
	
	glActiveTexture(GL_TEXTURE0);
	texture.BindTexture();
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, (void*) 0);
	glBindVertexArray(0);
}
	
float Planet::GetSpinVelocity() const
{
	return spinVelocity;
}

void Planet::SetSpinVelocity(float pSpinVelocity)
{
	spinVelocity = pSpinVelocity;
}