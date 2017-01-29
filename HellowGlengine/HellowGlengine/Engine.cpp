#include "stdafx.h"
#include "Engine.h"

#include "WindowFactory.h"
#include "../CommonUtilities/Timer.h"

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
	SAFE_DELETE(ourInstance);
}

CEngine& CEngine::GetInstance()
{
	assert(ourInstance != nullptr && "Engine not created (is NULL)");
	return *ourInstance;
}

CEngine* CEngine::GetInstancePtr()
{
	return ourInstance;
}

void CEngine::Start()
{
	if (myInitCallback)
	{
		myInitCallback();
	}

	while (myWindow->IsOpen() == true)
	{
		myWindow->Update();
		myLogicTimer->Update();

		if (myUpdateCallback)
		{
			myUpdateCallback(myLogicTimer->GetDeltaTime());
		}

		myGraphicsFramework->ClearFrame();

		if (myRenderCallback)
		{
			myRenderCallback();
		}

		myGraphicsFramework->Present();
	}
}

void CEngine::Shutdown()
{
	if (myWindow)
	{
		myWindow->Close();
	}
}

CEngine::CEngine()
	: myWindow(nullptr)
	, myGraphicsFramework(nullptr)
	, myInitCallback(nullptr)
	, myUpdateCallback(nullptr)
	, myRenderCallback(nullptr)
{
}

CEngine::~CEngine()
{
	SAFE_DELETE(myWindow);
	SAFE_DELETE(myGraphicsFramework);
}

bool CEngine::InternalInit(const SCreationParameters& aCreationParameters)
{
	if (aCreationParameters.myCreationFlags & SCreationParameters::eWindows && aCreationParameters.myCreationFlags & SCreationParameters::eLinux) return false;
	if (aCreationParameters.myCreationFlags & SCreationParameters::eGL && aCreationParameters.myCreationFlags & SCreationParameters::eDX) return false;

	myWindow = CWindowFactory::CreateWindow(aCreationParameters.myCreationFlags);

	IOSWindow::SCreationParameters windowCreationParameters = {};
	windowCreationParameters.myWindowWidth = aCreationParameters.myWindowWidth;
	windowCreationParameters.myWindowHeight = aCreationParameters.myWindowHeight;
	windowCreationParameters.myIsWindowed = (aCreationParameters.myCreationFlags ^ SCreationParameters::eFullScreen) > 0u;
	if (myWindow->Init(windowCreationParameters) == false)
	{
		SAFE_DELETE(myWindow);
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

	myInitCallback = aCreationParameters.myInitCallback;
	myUpdateCallback = aCreationParameters.myUpdateCallback;
	myRenderCallback = aCreationParameters.myRenderCallback;

	myLogicTimer = new CU::CTimer();

	return true;
}
