#include "stdafx.h"

#include "../CommonUtilities/WorkPool.h"
#include "../CommonUtilities/Work.h"

#include "WindowFactory.h"
#include "GraphicsFrameworkFactory.h"
#include "MeshManager.h"
#include "EffectManager.h"
#include "TextureManager.h"

#include "SpriteManager.h"
#include "Renderer.h"
#include "InputManager.h"

namespace wendy
{
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

	void CEngine::Start()
	{
		if (myInitCallback)
		{
			myInitCallback();
		}
		myInputManager->Start();
		Work inputWork([this] () { myInputManager->Update(); }, [this]() -> bool { return !myInputManager->IsRunning(); });
		inputWork.SetName("InputThread");
		//Work renderWork([this] () { Render(); }, [this]() -> bool { return !myWindow->IsOpen(); });
		//renderWork.SetName("RenderThread");

		WorkPool::Init(true);
		WorkPool::AddWork(std::move(inputWork));
		//WorkPool::AddWork(std::move(renderWork));

		while (myWindow->IsOpen() == true)
		{
			Update();
			Render();
		}
	}

	void CEngine::Shutdown()
	{
		myInputManager->Stop();

		if (myWindow.IsValid())
		{
			myWindow->Close();
		}

		WorkPool::Shutdown();
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

		if (myRenderCallback)
		{
			myRenderer->SwapWrite();

			myRenderCallback();
		}
	}

	void CEngine::Render()
	{
		myGraphicsFramework->ClearFrame();

		myRenderer->SwapRead();
		myRenderer->Render();

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

		myMeshManager = myGraphicsFramework->CreateMeshManager();
		myTextureManager = myGraphicsFramework->CreateTextureManager();
		myEffectManager = myGraphicsFramework->CreateEffectManager();

		mySpriteManager = CU::MakeUnique<CSpriteManager>();
		myRenderer = CU::MakeUnique<CRenderer>();
		myInputManager = CU::MakeUnique<CInputManager>(*myWindow);

		Subscribe();

		return true;
	}

	IInputListener::eResult CEngine::TakeInput(const CInputMessage& /*aMessage*/)
	{
		return eResult::ePassOn;
	}
}
