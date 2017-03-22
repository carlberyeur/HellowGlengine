#include "stdafx.h"
#include "SpriteInstance.h"
#include "Sprite.h"
#include "SpriteManager.h"

#include "Renderer.h"
#include "RenderSpriteCommand.h"

namespace wendy
{
	CSpriteInstance::CSpriteInstance()
	{
	}

	CSpriteInstance::CSpriteInstance(CSpriteInstance&& aCopy)
		: myPosition(aCopy.myPosition)
		, mySprite(std::move(aCopy.mySprite))
	{
	}

	CSpriteInstance::CSpriteInstance(const CSpriteInstance& aCopy)
		: myPosition(aCopy.myPosition)
	{
		if (aCopy.mySprite.IsValid())
		{
			mySprite = CEngine::GetInstance().GetSpriteManager().CopySprite(*aCopy.mySprite);
		}
	}

	CSpriteInstance::~CSpriteInstance()
	{
	}

	CSpriteInstance& CSpriteInstance::operator=(CSpriteInstance&& aCopy)
	{
		myPosition = aCopy.myPosition;
		mySprite = std::move(aCopy.mySprite);

		return *this;
	}

	CSpriteInstance& CSpriteInstance::operator=(const CSpriteInstance& aCopy)
	{
		myPosition = aCopy.myPosition;

		if (aCopy.mySprite.IsValid())
		{
			mySprite = CEngine::GetInstance().GetSpriteManager().CopySprite(*aCopy.mySprite);
		}

		return *this;
	}

	void CSpriteInstance::Init(const std::string& aTexturePath)
	{
		mySprite = CEngine::GetInstance().GetSpriteManager().CreateSprite(aTexturePath);
	}

	void CSpriteInstance::Render()
	{
		IRenderCommand* renderSprite = new CRenderSpriteCommand(mySprite.GetRawPointer(), myPosition);
		CEngine::GetInstance().GetRenderer().AddRenderCommand(renderSprite);

		//mySprite->Render(myPosition);
	}
}
