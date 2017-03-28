#include "stdafx.h"

#include "../Engine/Engine.h"
#include "../Game/Game.h"

wendy::CEngine::SCreationParameters::eCreationFlags GetOperatingSystem();

int Init(int argc, wchar_t* argv[]);

int wmain(int argc, wchar_t* argv[])
{
	//__try
	{
		Init(argc, argv);
	}
	//__except (auto e)
	{

	}
}

int Init(int argc, wchar_t * argv[])
{
	int exitResult = EXIT_FAILURE;
	CommandLineManager<wchar_t>::CreateInstance(argc, argv);
	DL_Debug::Debug::CreateInstance();

	{
		CGame game;

		wendy::CEngine::SCreationParameters creationParameters = {};
		creationParameters.myInitCallback = std::bind(&CGame::Init, &game);
		creationParameters.myUpdateCallback = std::bind(&CGame::Update, &game, std::placeholders::_1);
		creationParameters.myRenderCallback = std::bind(&CGame::Render, &game);
		creationParameters.myWindowWidth = 1920u;
		creationParameters.myWindowHeight = 1080u;
		creationParameters.myCreationFlags = 0u;
		creationParameters.myCreationFlags |= wendy::CEngine::SCreationParameters::eCreationFlags::eGL;
		creationParameters.myCreationFlags |= wendy::CEngine::SCreationParameters::eCreationFlags::eFullScreen;
		creationParameters.myCreationFlags |= GetOperatingSystem();


		if (wendy::CEngine::CreateInstance(creationParameters))
		{
			wendy::CEngine::GetInstance().Start();
			exitResult = EXIT_SUCCESS;
		}

	}

	wendy::CEngine::GetInstance().Shutdown();
	wendy::CEngine::DestroyInstance();

	//CU::IMemoryManagedObject::CollectRemainingGarbage();

	DL_Debug::Debug::DestroyInstance();
	CommandLineManager<wchar_t>::DestroyInstance();

	return exitResult;
}

wendy::CEngine::SCreationParameters::eCreationFlags GetOperatingSystem()
{
#ifdef _WIN32
	return wendy::CEngine::SCreationParameters::eCreationFlags::eWindows;
#elif defined(_APPLE_)
	return wendy::CEngine::SCreationParameters::eCreationFlags::eMac;
#elif defined(_LINUX)
	return  wendy::CEngine::SCreationParameters::eCreationFlags::eLinux;
#else
#error "What operating system is this?"
#endif // _WIN32
}
