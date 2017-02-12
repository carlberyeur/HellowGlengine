#include "stdafx.h"
#include "Engine.h"

#include "WindowFactory.h"

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

//temp includes
#include "GLRenderObject.h"
#include "GLEffect.h"

void CEngine::Start()
{
	if (myInitCallback)
	{
		myInitCallback();
	}

	CGLRenderObject renderObject;
	bool cool = renderObject.Init();
	if (!cool)
	{
		int apa = 0;
		apa++;
	}

	//CGLEffect effect;
	//bool coolio = effect.Init("Shaders/VS_Pos.glsl", "", "Shaders/FS_Pos.glsl", 0);
	//if (!coolio)
	//{
	//	int apa = 0;
	//	apa++;
	//}

	while (myWindow->IsOpen() == true)
	{
		myWindow->Update();
		myLogicTimer->Update();

		if (myUpdateCallback)
		{
			myUpdateCallback(myLogicTimer->GetDeltaTime());
		}

		myGraphicsFramework->ClearFrame();

		//effect.Activate();
		renderObject.Render();

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
	: myInitCallback(nullptr)
	, myUpdateCallback(nullptr)
	, myRenderCallback(nullptr)
	, myWindow(nullptr)
	, myGraphicsFramework(nullptr)
	, myLogicTimer(nullptr)
	, myRenderTimer(nullptr)
{
}

CEngine::~CEngine()
{
	SAFE_DELETE(myWindow);
	SAFE_DELETE(myGraphicsFramework);
	SAFE_DELETE(myLogicTimer);
	SAFE_DELETE(myRenderTimer);
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

	myLogicTimer = new CU::CStopWatch();

	return true;
}
