#include "stdafx.h"
#include "WindowFactory.h"

IOSWindow* CWindowFactory::CreateWindow(const unsigned int aEngineCreationFlags)
{
	IOSWindow* window = nullptr;
	if (aEngineCreationFlags & CEngine::SCreationParameters::eWindows)
	{
		window = new CWindowsWindow();
	}
	else if (aEngineCreationFlags & CEngine::SCreationParameters::eCreationFlags::eLinux)
	{
		// not implemented
	}
	else
	{
	}

	return window;
}
