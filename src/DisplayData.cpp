#include "DisplayData.hpp"

// 8K Resolution
const unsigned int DisplayData::MAX_WIDTH = 7680;
// 8K Resolution
const unsigned int DisplayData::MAX_HEIGHT = 4320;

// Defaults width and height to screen width and height
DisplayData::DisplayData(const GLFWvidmode* vidmode) : width(vidmode->width), height(vidmode->height), fullscreen(true) {}

unsigned int DisplayData::GetWidth() const
{
	return width;
}

unsigned int DisplayData::GetHeight() const
{
	return height;
}

float DisplayData::GetAspectRatio() const
{
	return (float) width / (float) height;
}

void DisplayData::SetDimensions(unsigned int pWidth, unsigned int pHeight)
{
	if (pWidth == 0 || pHeight == 0 || pWidth > MAX_WIDTH || pHeight > MAX_HEIGHT)
	{
		return;
	}
	
	if (width == pWidth && height == pHeight)
	{
		return;
	}
	
	width = pWidth;
	height = pHeight;
	
	if (onDimensionsChange != nullptr)
	{
		onDimensionsChange();
	}
}

void DisplayData::SetOnDimensionsChange(std::function<void()> pOnDimensionsChange)
{
	onDimensionsChange = pOnDimensionsChange;
}

bool DisplayData::IsFullscreen() const
{
	return fullscreen;
}

void DisplayData::SetFullscreen(bool pFullscreen)
{
	if (fullscreen == pFullscreen)
	{
		return;
	}
	
	fullscreen = pFullscreen;
	
	if (onFullscreenChange != nullptr)
	{
		onFullscreenChange();
	}
}

void DisplayData::ToggleFullscreen()
{
	fullscreen = !fullscreen;
	
	if (onFullscreenChange != nullptr)
	{
		onFullscreenChange();
	}
}

void DisplayData::SetOnFullscreenChange(std::function<void()> pOnFullscreenChange)
{
	onFullscreenChange = pOnFullscreenChange;
}