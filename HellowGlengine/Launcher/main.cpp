#include "stdafx.h"

#include "../HellowGlengine/Engine.h"
#include "../Game/Game.h"

#include "../CommonUtilities/Time.h"
#include "../CommonUtilities/CommandLineParser.h"

CEngine::SCreationParameters::eCreationFlags GetOperatingSystem();

int main(int argc, char* argv[])
{
	argc; argv;

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


		if (CEngine::CreateInstance(creationParameters) == false)
		{
			return EXIT_FAILURE;
		}

		CEngine::GetInstance().Start();
	}

	CEngine::GetInstance().Shutdown();
	CEngine::DestroyInstance();

	return EXIT_SUCCESS;
}

CEngine::SCreationParameters::eCreationFlags GetOperatingSystem()
{
#ifdef _WIN32
	return CEngine::SCreationParameters::eCreationFlags::eWindows;
#elif defined(_LINUX)
	return  CEngine::SCreationParameters::eCreationFlags::eLinux;
#endif // _WIN32
}
