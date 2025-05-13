#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTextureCoord;

uniform vec3 objectColor;
uniform vec3 dirLightColor;
uniform vec3 dirLightVector;
uniform vec3 pointLightColor;
uniform vec3 pointLightPos;
uniform vec3 viewPos;
uniform sampler2D textureSampler;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * (pointLightColor + dirLightColor);
	
	vec3 norm = normalize(fragNormal);
	vec3 pointLightVector = normalize(pointLightPos - fragPos);

	float pointDiff = max(dot(norm, pointLightVector), 0.0);
	float dirDiff = max(dot(norm, dirLightVector), 0.0);
	vec3 diffuse = (pointDiff * pointLightColor + dirDiff * dirLightColor);
	
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 pointReflectDir = reflect(-pointLightVector, norm);
	vec3 dirReflectDir = reflect(-dirLightVector, norm);
	
	float specularStrength = 0.5;
	float pointSpecularIntensity = pow(max(dot(viewDir, pointReflectDir), 0.0), 4);
	float dirSpecularIntensity = pow(max(dot(viewDir, dirReflectDir), 0.0), 4);
	vec3 specular = specularStrength * (pointSpecularIntensity * pointLightColor + dirSpecularIntensity * dirLightColor);
	
	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = texture(textureSampler, fragTextureCoord).rrra * vec4(result, 1.0);
}