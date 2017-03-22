#include "stdafx.h"
#include "SpriteInstance.h"
#include "Sprite.h"
#include "SpriteManager.h"

namespace wendy
{
	CSpriteInstance::CSpriteInstance()
	{
	}

	CSpriteInstance::CSpriteInstance(const CSpriteInstance& aCopy)
		: myPosition(aCopy.myPosition)
		, mySprite(CU::MakeUnique<CSprite, SSpriteDeleter>(*aCopy.mySprite))
	{
	}

	CSpriteInstance::~CSpriteInstance()
	{
	}

	void CSpriteInstance::Init(const std::string& aTexturePath)
	{
		mySprite = CEngine::GetInstance().GetSpriteManager().CreateSprite(aTexturePath);
	}

	void CSpriteInstance::Render()
	{
		mySprite->Render(myPosition);
	}
}
