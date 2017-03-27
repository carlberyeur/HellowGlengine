#include "stdafx.h"
#include "SpriteInstance.h"
#include "Sprite.h"
#include "SpriteManager.h"

#include "Renderer.h"
#include "RenderSpriteCommand.h"

namespace wendy
{
	CSpriteInstance::CSpriteInstance()
		: myTextureRect({ { 0.f, 0.f }, { 1.f, 1.f } })
	{
	}

	CSpriteInstance::CSpriteInstance(CSpriteInstance&& aCopy)
		: myTextureRect(aCopy.myTextureRect)
		, myPosition(aCopy.myPosition)
		, mySprite(std::move(aCopy.mySprite))
	{
	}

	CSpriteInstance::CSpriteInstance(const CSpriteInstance& aCopy)
		: myTextureRect(aCopy.myTextureRect)
		, myPosition(aCopy.myPosition)
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
		myTextureRect = aCopy.myTextureRect;
		myPosition = aCopy.myPosition;
		mySprite = std::move(aCopy.mySprite);

		return *this;
	}

	CSpriteInstance& CSpriteInstance::operator=(const CSpriteInstance& aCopy)
	{
		myTextureRect = aCopy.myTextureRect;
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
		IRenderCommand* renderSprite = new CRenderSpriteCommand(mySprite.GetRawPointer(), myTextureRect, myPosition);
		CEngine::GetInstance().GetRenderer().AddRenderCommand(renderSprite);
	}

	CU::Vector2f CSpriteInstance::GetSize() const
	{
		return mySprite->GetTextureSize();
	}
}
