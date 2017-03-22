#include "stdafx.h"
#include "LevelLoader.h"

CLevelLoader* CLevelLoader::ourInstance = nullptr;

CLevelLoader::CLevelLoader(CLevel& aLevel, CScene& aScene)
	: myLevel(aLevel)
	, myScene(aScene)
{
	assert(ourInstance == nullptr);
	ourInstance = this;
}

CLevelLoader::~CLevelLoader()
{
	assert(ourInstance == this);
	ourInstance = nullptr;
}

CLevelLoader* CLevelLoader::GetInstance()
{
	return ourInstance;
}
