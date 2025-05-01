#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureCoord;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vertexPos, 1.0f);
	fragPos = vec3(model * vec4(vertexPos, 1.0));
	fragNormal = mat3(transpose(inverse(model))) * vertexNormal;
	fragTextureCoord = vertexTextureCoord;
}