#include "Texture.hpp"

#include "stb_image.h"

#include "gLErrorHandle.hpp"

static const float BORDER_COLOR[] = { 1.0f, 0.0f, 1.0f, 1.0f };

Texture::Texture(const char* texturePath) : Texture(texturePath, GL_RGB)
{
}

Texture::Texture(const char* texturePath, GLenum format)
{
	GLCall(glGenTextures(1, &ID));
	BindTexture();
	
	GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BORDER_COLOR));
	
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	
	if (data != nullptr)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		std::cout << "Failed to load texture: " << texturePath << std::endl;
	}
	
	stbi_image_free(data);
	UnbindTexture();
}

Texture::~Texture()
{
}

void Texture::BindTexture() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));
}

void Texture::UnbindTexture() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}