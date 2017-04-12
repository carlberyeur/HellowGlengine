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
		if (mySpriteLookup.find(aSpritePath) == mySpriteLookup.end())
		{
			CSprite* newSprite = new CSprite();
			newSprite->Init(aSpritePath);
			
			int newIndex = mySprites.Size();
			mySpriteLookup[aSpritePath] = newIndex;
			mySprites.Add(newSprite);
		}

		int index = mySpriteLookup[aSpritePath];
		CSprite* sprite = mySprites[index];
		sprite->AddRef();
		return CU::UniquePointer<CSprite, SSpriteDeleter>(sprite);
	}

	CU::UniquePointer<CSprite, SSpriteDeleter> CSpriteManager::CopySprite(const CSprite& aSprite)
	{
		CU::UniquePointer<CSprite, SSpriteDeleter> newSprite = CU::MakeUnique<CSprite, SSpriteDeleter>(aSprite);
		newSprite->AddRef();
		return newSprite;
	}

	void CSpriteManager::DestroySprite(CSprite* aSprite)
	{
		std::lock_guard<std::mutex> lock(myDeleteSpritesLock);
		if (aSprite->DecRef() > 0)
		{
			return;
		}

		if (mySprites.RemoveCyclic(aSprite))
		{
			myDeadSprites.Add(aSprite);
		}
	}

	std::string CSpriteManager::GetSpritePath(const CSprite& aSprite) const
	{
		//int spriteIndex = mySprites.Find(&aSprite);
		for (int i = 0; i < mySprites.Size(); ++i)
		{
			if (mySprites[i] == &aSprite)
			{
				for (const auto& lookup : mySpriteLookup)
				{
					if (lookup.second == i)
					{
						return lookup.first;
					}
				}

				break;
			}
		}

		return std::string();
	}

	void CSpriteManager::CollectGarbage()
	{
		std::lock_guard<std::mutex> lock(myDeleteSpritesLock);
		myDeadSprites.DeleteAll();
	}
}
