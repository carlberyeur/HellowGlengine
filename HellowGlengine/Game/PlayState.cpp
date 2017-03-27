#include "stdafx.h"
#include "PlayState.h"

#include "Level.h"
#include "Scene.h"

#include "LevelLoader.h"
#include "TiledLoader.h"

#include "../Engine/SpriteInstance.h"

CPlayState::CPlayState(CStateStack& aStateStack)
	: IState(aStateStack)
{
}

CPlayState::~CPlayState()
{
}

void CPlayState::Init()
{
	myLevel = new CLevel();
	if (!myLevel)
	{
		return;
	}

	myScene = new CScene();
	if (!myScene)
	{
		return;
	}

	CLevelLoader levelLoader(*myLevel, *myScene);
	levelLoader.RegisterLoadFunction("root", TiledLoader::LoadRoot);
	levelLoader.RegisterLoadFunction("layers", TiledLoader::LoadLayers);
	levelLoader.RegisterLoadFunction("tilelayer", TiledLoader::LoadTileLayer);
	levelLoader.RegisterLoadFunction("tilesets", TiledLoader::LoadTileSets);
	levelLoader.RegisterLoadFunction("objects", TiledLoader::LoadObjects);
	levelLoader.LoadLevel("Data/Levels/sewers.json");

	for (STileData& tile : levelLoader.GetTileDatas())
	{
		wendy::CSpriteInstance spriteInstance;

		std::string spritePath;
		for (STileSet& tileSet : levelLoader.GetTileSets())
		{
			if (tileSet.firstgid <= tile.gid && tileSet.firstgid + tileSet.tileCount > tile.gid)
			{
				spritePath = tileSet.texture;
				spriteInstance.SetPosition(static_cast<float>(tile.posx * 24) / (float)tileSet.imageSize.x, static_cast<float>(tile.posy * 24) / (float)tileSet.imageSize.y);
				spriteInstance.Init(spritePath);
				//get uvs too
				break;
			}
		}

		myScene->AddSpriteInstance(std::move(spriteInstance));
	}
	
	myLevel->Init();
	myScene->Init();
}

eStateStatus CPlayState::Update(const CU::Time& aDeltaTime)
{
	myLevel->Update(aDeltaTime);
	myScene->Update(aDeltaTime);

	return eStateStatus::eKeep;
}

void CPlayState::Render()
{
	myScene->Render();
}

void CPlayState::OnEnter()
{
}

void CPlayState::OnExit()
{
}
