#include "stdafx.h"
#include "Engine.h"

#include "WindowFactory.h"
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
#include "GLTexture.h"
#include "GLTextureManager.h"
#include "EInputLayout.h"

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

	ITexture* tex;
	CGLTextureManager man;
	man.LoadTexture("Textures/square.tga", tex);

	CGLEffect effect;
	bool coolio = effect.Init("Shaders/VS_", "", "Shaders/FS_", eInputLayout::eInputLayout_ePos | eInputLayout::eInputLayout_eTex);
	if (!coolio)
	{
		BREAK_POINT_HERE;
	}

	std::thread inputThread(&CInputManager::Start, myInputManager.GetRawPointer());

	while (myWindow->IsOpen() == true)
	{
		myWindow->Update();
		myLogicTimer->Update();

		myInputManager->DispatchMessages();

		if (myUpdateCallback)
		{
			myUpdateCallback(myLogicTimer->GetDeltaTime());
		}

		myGraphicsFramework->ClearFrame();

		effect.Activate();
		renderObject.Render();

		if (myRenderCallback)
		{
			myRenderCallback();
		}

		myGraphicsFramework->Present();
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

	IOSWindow::SCreationParameters windowCreationParameters = {};
	windowCreationParameters.myWindowWidth = aCreationParameters.myWindowWidth;
	windowCreationParameters.myWindowHeight = aCreationParameters.myWindowHeight;
	windowCreationParameters.myIsWindowed = (aCreationParameters.myCreationFlags ^ SCreationParameters::eFullScreen) > 0u;
	if (!myWindow->Init(windowCreationParameters))
	{
		return false;
	}

	if (aCreationParameters.myCreationFlags & SCreationParameters::eGL)
	{
		myGraphicsFramework = CU::MakeUnique<IGraphicsFramework, COpenGLFramework>();
		if (!myGraphicsFramework->Init(*myWindow))
		{
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

	myLogicTimer = CU::MakeUnique<CU::CStopWatch>();

	myInputManager = CU::MakeUnique<CInputManager>(*myWindow);
	Subscribe();

	return true;
}

IInputListener::eResult CEngine::TakeInput(const CInputMessage& aMessage)
{
	return eResult::ePassOn;
}
