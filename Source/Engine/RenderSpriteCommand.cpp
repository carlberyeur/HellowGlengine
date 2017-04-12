#include "stdafx.h"
#include "RenderSpriteCommand.h"
#include "Sprite.h"
#include "TextureRect.h"

namespace wendy
{
	CRenderSpriteCommand::CRenderSpriteCommand(CSprite* aSprite, const STextureRect& aTextureRect, const CU::Vector2f aPosition, const CU::Vector2f aScale)
		: myTextureRect(aTextureRect)
		, myPosition(aPosition)
		, myScale(aScale)
		, mySprite(aSprite)
	{
	}
	
	CRenderSpriteCommand::~CRenderSpriteCommand()
	{
	}

	void CRenderSpriteCommand::Do()
	{
		mySprite->Render(myPosition, myScale, myTextureRect);
	}
}
