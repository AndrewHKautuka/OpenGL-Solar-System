#include "PointLightSource.hpp"

PointLightSource::PointLightSource(float pRadius, vec3 pPosition, unsigned int pStackCount, ShaderProgram* pShader, vec3 pLightColor) : LightSource(pShader, pLightColor), mesh(pRadius, pStackCount * 2, pStackCount, true, 2)
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
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	position = pPosition;
	modelMatrix = mat4(1.0f);
}

PointLightSource::~PointLightSource()
{
}

void PointLightSource::Update()
{
	modelMatrix = mat4(1.0f);
	modelMatrix = translate(modelMatrix, position);
}

void PointLightSource::Draw(mat4* projectionMatrix, mat4* viewMatrix) const
{
	LightSource::Draw(projectionMatrix, viewMatrix);
	shader->setMat4("projection", *projectionMatrix);
	shader->setMat4("view", *viewMatrix);
	shader->setMat4("model", modelMatrix);
}

void PointLightSource::ApplyToShader(ShaderProgram* const shader)
{
	shader->setVec3("pointLightColor", lightColor);
	shader->setVec3("pointLightPos", position);
}