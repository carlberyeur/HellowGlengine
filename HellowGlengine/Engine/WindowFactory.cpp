#include "stdafx.h"
#include "WindowFactory.h"

CU::UniquePointer<IOSWindow> CWindowFactory::CreateWindow(const unsigned int aEngineCreationFlags)
{
	CU::UniquePointer<IOSWindow> window;
	if (aEngineCreationFlags & CEngine::SCreationParameters::eWindows)
	{
		window = CU::MakeUnique<IOSWindow, CWindowsWindow>();
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
