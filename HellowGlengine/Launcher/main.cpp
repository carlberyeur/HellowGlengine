#include "stdafx.h"

#include "../HellowGlengine/Engine.h"
#include "../Game/Game.h"

int main(int argc, char* argv[])
{
	argc; argv;

	{
		CGame game;

		CEngine::SCreationParameters createionParameters = {};
		createionParameters.myWindowWidth = 1920u;
		createionParameters.myWindowHeight = 1080u;
		createionParameters.myCreationFlags = 0;
		createionParameters.myCreationFlags |= CEngine::SCreationParameters::eCreationFlags::eGL;
		createionParameters.myCreationFlags |= CEngine::SCreationParameters::eCreationFlags::eFullScreen;
		createionParameters.myCreationFlags |= CEngine::SCreationParameters::eCreationFlags::eWindows;

		if (CEngine::CreateInstance(createionParameters) == false)
		{
			return EXIT_FAILURE;
		}

		CEngine::GetInstance().Start();
	}

	CEngine::GetInstance().Shutdown();
	CEngine::DestroyInstance();

	return EXIT_SUCCESS;
}
