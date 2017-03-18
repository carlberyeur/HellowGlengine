#include "stdafx.h"

#include "../Engine/Engine.h"
#include "../Game/Game.h"

#pragma comment(lib, "../Dependencies/python34/libs/python34.lib")

CEngine::SCreationParameters::eCreationFlags GetOperatingSystem();

int wmain(int argc, wchar_t* argv[])
{
	int exitResult = EXIT_FAILURE;
	CommandLineManager<wchar_t>::CreateInstance(argc, argv);
	DL_Debug::Debug::CreateInstance();

	{
		CGame game;

		CEngine::SCreationParameters creationParameters = {};
		creationParameters.myInitCallback = std::bind(&CGame::Init, &game);
		creationParameters.myUpdateCallback = std::bind(&CGame::Update, &game, std::placeholders::_1);
		creationParameters.myRenderCallback = std::bind(&CGame::Render, &game);
		creationParameters.myWindowWidth = 1920u;
		creationParameters.myWindowHeight = 1080u;
		creationParameters.myCreationFlags = 0u;
		creationParameters.myCreationFlags |= CEngine::SCreationParameters::eCreationFlags::eGL;
		creationParameters.myCreationFlags |= CEngine::SCreationParameters::eCreationFlags::eFullScreen;
		creationParameters.myCreationFlags |= GetOperatingSystem();


		if (CEngine::CreateInstance(creationParameters))
		{
			CEngine::GetInstance().Start();
			exitResult = EXIT_SUCCESS;
		}

	}

	CEngine::GetInstance().Shutdown();
	CEngine::DestroyInstance();

	DL_Debug::Debug::DestroyInstance();
	CommandLineManager<wchar_t>::DestroyInstance();

	return exitResult;
}

CEngine::SCreationParameters::eCreationFlags GetOperatingSystem()
{
#ifdef _WIN32
	return CEngine::SCreationParameters::eCreationFlags::eWindows;
#elif defined(_LINUX)
	return  CEngine::SCreationParameters::eCreationFlags::eLinux;
#elif defined(_APPLE_)
	return CEngine::SCreationParameters::eCreationFlags::eMac;
#else
#error "What operating system is this?"
	return  CEngine::SCreationParameters::eCreationFlags::eLinux;
#endif // _WIN32
}
