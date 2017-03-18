#include "stdafx.h"

#include "WindowFactory.h"
#include "GraphicsFrameworkFactory.h"
#include "InputManager.h"

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
	assert(ourInstance != nullptr && "Engine not created (is NULL)");
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
#include "OpenGLFramework.h"
#include <Windows.h>
#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"

#undef CreateWindow

#include "GLRenderObject.h"
#include "GLEffect.h"
#include "GLTexture.h"
#include "GLTextureManager.h"
#include "EInputLayout.h"

CGLRenderObject renderObject;
CGLEffect effect;
ITexture* tex;
GLenum error;

void CEngine::Start()
{
	if (myInitCallback)
	{
		myInitCallback();
	}

	bool cool = renderObject.Init();
	if (!cool)
	{
		int apa = 0;
		apa++;
	}

	CGLTextureManager man;
	man.LoadTexture("Textures/square.tga", tex);

	bool coolio = effect.Init("Shaders/VS_", "", "Shaders/FS_", eInputLayout::eInputLayout_ePos | eInputLayout::eInputLayout_eTex);
	if (!coolio)
	{
		BREAK_POINT_HERE;
	}

	std::thread inputThread(&CInputManager::Start, myInputManager.GetRawPointer());

	while (myWindow->IsOpen() == true)
	{
		Update();
		Render();
	}

	myInputManager->Stop();
	inputThread.join();
}

void CEngine::Shutdown()
{
	if (myWindow.IsValid())
	{
		myWindow->Close();
	}
}

void CEngine::Update()
{
	myWindow->Update();
	myLogicTimer->Update();

	myInputManager->DispatchMessages();

	if (myUpdateCallback)
	{
		if (!myUpdateCallback(myLogicTimer->GetDeltaTime()))
		{
			myWindow->Close();
		}
	}
}

void CEngine::Render()
{
	myGraphicsFramework->ClearFrame();

	effect.Activate();
	renderObject.Render();

	if (myRenderCallback)
	{
		myRenderCallback();
	}

	myGraphicsFramework->Present();
}

CEngine::CEngine()
	: myInitCallback(nullptr)
	, myUpdateCallback(nullptr)
	, myRenderCallback(nullptr)
{
}

CEngine::~CEngine()
{
}

bool CEngine::InternalInit(const SCreationParameters& aCreationParameters)
{
	if (aCreationParameters.myCreationFlags & SCreationParameters::eWindows && aCreationParameters.myCreationFlags & SCreationParameters::eLinux) return false;
	if (aCreationParameters.myCreationFlags & SCreationParameters::eGL && aCreationParameters.myCreationFlags & SCreationParameters::eDX) return false;

	myWindow = CWindowFactory::CreateWindow(aCreationParameters.myCreationFlags);
	if (!myWindow)
	{
		return false;
	}

	IWindow::SCreationParameters windowCreationParameters = {};
	windowCreationParameters.myWindowWidth = aCreationParameters.myWindowWidth;
	windowCreationParameters.myWindowHeight = aCreationParameters.myWindowHeight;
	windowCreationParameters.myIsWindowed = (aCreationParameters.myCreationFlags & SCreationParameters::eFullScreen) > 0u;
	if (!myWindow->Init(windowCreationParameters))
	{
		return false;
	}

	myGraphicsFramework = CGraphicsFrameworkFactory::CreateFramework(aCreationParameters.myCreationFlags, *myWindow);
	if (!myGraphicsFramework)
	{
		return false;
	}

	myInitCallback = aCreationParameters.myInitCallback;
	myUpdateCallback = aCreationParameters.myUpdateCallback;
	myRenderCallback = aCreationParameters.myRenderCallback;

	myLogicTimer = CU::MakeUnique<CU::CStopWatch>();

	myInputManager = CU::MakeUnique<CInputManager>(*myWindow);
	Subscribe();

	return true;
}

IInputListener::eResult CEngine::TakeInput(const CInputMessage& /*aMessage*/)
{
	return eResult::ePassOn;
}
