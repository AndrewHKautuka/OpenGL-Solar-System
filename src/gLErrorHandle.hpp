// Description
// OpenGL, by default, does not print out the errors it encounters as it processes functions.
// The purpose of this file is to provide functionality to allow the developer to be notified of errors that occur, without the use of external tools.
// This supports debugging of bugs that would otherwise be difficult to detect.
//
// OpenGl's errors are handled as flags in its internal memory.
// glGetError() returns an error flag of a single error whose flag has been set.
// If multiple error flags have been set, then glGetError() must be ran multiple times to get all error flags.
// The order of the error flags returned is arbitrary.
// If there are no errors - or all error flags have already been returned - glGetError() returns GL_NO_ERROR.
//
// Uses C++ marcos
//
// Usable from OpenGL 1.1
//
// Reference
// Chernikov, Y. (2017, November 12). Dealing with Errors in OpenGL [Video]. YouTube. https://www.youtube.com/watch?v=FBbPWSOQ0-w
//
#pragma once

#include <glad/glad.h>
#include <iostream>

// Causes debugger to break on line this is called
#define ASSERT(x) if (!(x)) __debugbreak();

// Clears pending errors before expression/function x, invokes x, then logs any errors generated
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Clear all pending errors
static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

// function - the signature of the function that errored
// file - filename with function invokation that errored
// line - file line with function invokation that errored
static bool GLLogCall(const char* function, const char* file, int line)
{
	bool noError = true;
	while (GLenum error = glGetError()) // Will run until error is 0, ie GL_NO_ERROR
	{
		std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function << " " << file << ":" << line << std::endl;
		noError = false;
	}
	return noError;
}