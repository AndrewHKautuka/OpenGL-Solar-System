#pragma once

#include <glad/glad.h>

class Texture
{
public:
	Texture(const char* texturePath, GLenum format);
	Texture(const char* texturePath);
	~Texture();
	
	void BindTexture() const;
	void UnbindTexture() const;
private:
	unsigned int ID;
	int width, height, nrChannels;
};