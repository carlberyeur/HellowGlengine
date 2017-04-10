#include "stdafx.h"
#include "PlayState.h"

#include "Level.h"
#include "Scene.h"

#include "LevelLoader.h"
#include "TiledLoader.h"

#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "ScriptComponent.h"

#include "../Engine/SpriteInstance.h"
#include "../Engine/Engine.h"

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
				spriteInstance.Init(spritePath);
				
				CU::Vector2f tilePosition(static_cast<float>(tile.posx * 24) / (float)tileSet.imageSize.x, static_cast<float>(tile.posy * 24) / (float)tileSet.imageSize.y);
				tilePosition *= CU::Vector2f(tileSet.imageSize) / wendy::CEngine::GetInstance().GetWindowSizeF();
				spriteInstance.SetPosition(tilePosition);

				spriteInstance.SetVirtualSize(tileSet.tileSize);

				unsigned int width = tileSet.columns;
				unsigned int tileIndex = tile.gid - tileSet.firstgid;
				unsigned int tileX = tileIndex % width;
				unsigned int tileY = tileIndex / width;
				tileX *= tileSet.tileSize.x;
				tileY *= tileSet.tileSize.y;
				
				wendy::STextureRect textureRect;
				textureRect.topleft.Set(tileX, tileY);
				textureRect.botright.Set(tileX + tileSet.tileSize.x, tileY + tileSet.tileSize.y);
				
				textureRect.topleft /= CU::Vector2f(tileSet.imageSize);
				textureRect.botright /= CU::Vector2f(tileSet.imageSize);


				spriteInstance.SetTextureRect(textureRect);
				break;
			}
		}

		myScene->AddSpriteInstance(std::move(spriteInstance));
	}

	
	CGameObject& playerObject = *myLevel->GetGameObject(myLevel->AddGameObject());

	CSpriteComponent* playerSprite = new CSpriteComponent("Textures/player.tga");
	playerObject.AddComponent(*playerSprite);
	CScriptComponent* playerScript = new CScriptComponent();
	playerScript->InitModule("player_movement");
	playerObject.AddComponent(*playerScript);
	playerObject.Init();

	myLevel->Init();
	myScene->Init();
}

eStateStatus CPlayState::Update(const CU::Time aDeltaTime)
{
	myLevel->Update(aDeltaTime);
	myScene->Update(aDeltaTime);

	return GetStatus();
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
