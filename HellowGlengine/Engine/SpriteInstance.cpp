#include "stdafx.h"
#include "SpriteInstance.h"
#include "Sprite.h"

CSpriteInstance::CSpriteInstance()
{
}

CSpriteInstance::CSpriteInstance(const CSpriteInstance& aCopy)
	: myPosition(aCopy.myPosition)
	, mySprite(CU::MakeUnique<CSprite>(*aCopy.mySprite))
{
}

CSpriteInstance::~CSpriteInstance()
{
}

void CSpriteInstance::Init(const std::string& aTexturePath)
{
	mySprite = CU::MakeUnique<CSprite>();
	mySprite->Init(aTexturePath);
}

void CSpriteInstance::Render()
{
	mySprite->Render(myPosition);
}
