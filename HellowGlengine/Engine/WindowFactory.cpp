#include "stdafx.h"
#include "WindowFactory.h"

CU::UniquePointer<IWindow> CWindowFactory::Create(const unsigned int aEngineCreationFlags)
{
	CU::UniquePointer<IWindow> window;
	if (aEngineCreationFlags & CEngine::SCreationParameters::eWindows)
	{
		window = CU::MakeUnique<CWindowsWindow>();
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
