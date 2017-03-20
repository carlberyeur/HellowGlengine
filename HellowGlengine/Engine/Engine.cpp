#include "stdafx.h"

#include "WindowFactory.h"
#include "GraphicsFrameworkFactory.h"
#include "TextureManager.h"
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
#include "GLRenderObject.h"
#include "GLEffect.h"
#include "GLTexture.h"
#include "GLTextureManager.h"
#include "EInputLayout.h"

#include "GLSprite.h"
CGLSprite* sprite = nullptr;
CGLSprite* sprite2 = nullptr;

void CEngine::Start()
{
	if (myInitCallback)
	{
		myInitCallback();
	}

	sprite = new CGLSprite();
	sprite2 = new CGLSprite();

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

	sprite->Render({ 0.25f, 0.5f });
	sprite2->Render({ 0.5f, 0.5f });

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

	myWindowSize.Set(aCreationParameters.myWindowWidth, aCreationParameters.myWindowHeight);

	myWindow = CWindowFactory::Create(aCreationParameters.myCreationFlags);
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

	myTextureManager = ITextureManager::Create(*myGraphicsFramework);
	myInputManager = CU::MakeUnique<CInputManager>(*myWindow);
	Subscribe();

	return true;
}

IInputListener::eResult CEngine::TakeInput(const CInputMessage& /*aMessage*/)
{
	return eResult::ePassOn;
}
