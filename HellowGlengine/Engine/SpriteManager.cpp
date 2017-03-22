#include "stdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"

namespace wendy
{
	void SSpriteDeleter::Destroy(CSprite* aSprite)
	{
		CEngine::GetInstance().GetSpriteManager().DestroySprite(aSprite);
	}

	CSpriteManager::CSpriteManager()
		: mySprites(32)
		, myDeadSprites(32)
	{
	}

	CSpriteManager::~CSpriteManager()
	{
		mySprites.DeleteAll();
		myDeadSprites.DeleteAll();
	}

	CU::UniquePointer<CSprite, SSpriteDeleter> CSpriteManager::CreateSprite(const std::string& aSpritePath)
	{
		CSprite* sprite = new CSprite();
		sprite->Init(aSpritePath);
		mySprites.Add(sprite);

		return CU::UniquePointer<CSprite, SSpriteDeleter>(sprite);
	}

	void CSpriteManager::DestroySprite(CSprite* aSprite)
	{
		std::lock_guard<std::mutex> lock(myDeleteSpritesLock);
		if (mySprites.RemoveCyclic(aSprite))
		{
			myDeadSprites.Add(aSprite);
		}
	}

	void CSpriteManager::CollectGarbage()
	{
		std::lock_guard<std::mutex> lock(myDeleteSpritesLock);
		myDeadSprites.DeleteAll();
	}
}
