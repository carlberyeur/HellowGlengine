#include "stdafx.h"
#include "Engine.h"

#include "OpenGLFramework.h"
#include "WindowsWindow.h"

CEngine* CEngine::ourInstance = nullptr;

bool CEngine::CreateInstance(const SCreationParameters& aCreationParameters)
{
	assert(ourInstance == nullptr && "Engine should not be created twice!");
	ourInstance = new CEngine();
	
	if (ourInstance != nullptr)
	{
		return ourInstance->InternalInit(aCreationParameters);
	}

	return false;
}

void CEngine::DestroyInstance()
{
}

CEngine& CEngine::GetInstance()
{
	assert(ourInstance != nullptr && "Engine not created (is NULL)");
	return *ourInstance;
}

void CEngine::Start()
{
	while (myWindow->IsOpen() == true)
	{
		myWindow->Update();
	}
}

void CEngine::Shutdown()
{
}

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}

bool CEngine::InternalInit(const SCreationParameters& aCreationParameters)
{
	if (aCreationParameters.myCreationFlags & SCreationParameters::eWindows)
	{
		myWindow = new CWindowsWindow();
		IOSWindow::SCreationParameters windowCreationParameters = {};
		windowCreationParameters.myWindowWidth = aCreationParameters.myWindowWidth;
		windowCreationParameters.myWindowHeight = aCreationParameters.myWindowHeight;
		windowCreationParameters.myIsWindowed = (aCreationParameters.myCreationFlags ^ SCreationParameters::eFullScreen) == 1u;
		if (myWindow->Init(windowCreationParameters) == false)
		{
			SAFE_DELETE(myWindow);
			return false;
		}
	}
	else if (aCreationParameters.myCreationFlags & SCreationParameters::eCreationFlags::eLinux)
	{
		return false; // not implemented
	}
	else
	{
		return false;
	}

	if (aCreationParameters.myCreationFlags & SCreationParameters::eGL)
	{
		myGraphicsFramework = new COpenGLFramework();
		if (myGraphicsFramework->Init(*myWindow) == false)
		{
			SAFE_DELETE(myGraphicsFramework);
			return false;
		}
	}
	else if (aCreationParameters.myCreationFlags & SCreationParameters::eDX)
	{
		return false; // not implemented
	}
	else
	{
		return false;
	}

	return true;
}
