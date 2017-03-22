#include "stdafx.h"
#include "RenderSpriteCommand.h"
#include "Sprite.h"

namespace wendy
{
	CRenderSpriteCommand::CRenderSpriteCommand(CSprite* aSprite, const CU::Vector2f aPosition)
		: myPosition(aPosition)
		, mySprite(aSprite)
	{
	}
	
	CRenderSpriteCommand::~CRenderSpriteCommand()
	{
	}

	void CRenderSpriteCommand::Do()
	{
		mySprite->Render(myPosition);
	}
}
