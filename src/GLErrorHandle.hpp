// Description:
// APA Reference: Chernikov, Y. (2017, November 12). Dealing with Errors in OpenGL [Video]. YouTube. https://www.youtube.com/watch?v=FBbPWSOQ0-w
#pragma once

#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function << " " << file << ":" << line << "\n";
		return false;
	}
	return true;
}