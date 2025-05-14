#pragma once

// glad is not used by InputBinding but regardless need to be included to ensure
// including GLFW does not throw a compilation error
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

struct DisplayData
{
public:
	static const unsigned int MAX_WIDTH;
	static const unsigned int MAX_HEIGHT;
private:
	unsigned int width, height;
	bool fullscreen;
	
	std::function<void()> onDimensionsChange, onFullscreenChange;
public:
	DisplayData(const GLFWvidmode* vidmode);
	
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	float GetAspectRatio() const;
	void SetDimensions(unsigned int pWidth, unsigned int pHeight);
	void SetOnDimensionsChange(std::function<void()> pOnDimensionsChange);
	
	bool IsFullscreen() const;
	void SetFullscreen(bool pFullscreen);
	void ToggleFullscreen();
	void SetOnFullscreenChange(std::function<void()> pOnFullscreenChange);
};