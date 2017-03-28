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
		, myScale(CU::Vector2f::One)
	{
	}

	CSpriteInstance::CSpriteInstance(CSpriteInstance&& aCopy)
		: myTextureRect(aCopy.myTextureRect)
		, myPosition(aCopy.myPosition)
		, myScale(aCopy.myScale)
		, mySprite(std::move(aCopy.mySprite))
	{
	}

	CSpriteInstance::CSpriteInstance(const CSpriteInstance& aCopy)
		: myTextureRect(aCopy.myTextureRect)
		, myPosition(aCopy.myPosition)
		, myScale(aCopy.myScale)
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
		myScale = aCopy.myScale;
		mySprite = std::move(aCopy.mySprite);

		return *this;
	}

	CSpriteInstance& CSpriteInstance::operator=(const CSpriteInstance& aCopy)
	{
		myTextureRect = aCopy.myTextureRect;
		myPosition = aCopy.myPosition;
		myScale = aCopy.myScale;

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
		IRenderCommand* renderSprite = new CRenderSpriteCommand(mySprite.GetRawPointer(), myTextureRect, myPosition, myScale);
		CEngine::GetInstance().GetRenderer().AddRenderCommand(renderSprite);
	}

	CU::Vector2f CSpriteInstance::GetSize() const
	{
		return mySprite->GetTextureSize();
	}

	void CSpriteInstance::SetVirtualSize(const CU::Vector2ui aVirtualPixelSize)
	{
		CU::Vector2f virtualSize(aVirtualPixelSize);
		myScale = virtualSize / mySprite->GetTextureSize();
	}

	std::string CSpriteInstance::GetFilePath() const
	{
		if (!mySprite)
		{
			return std::string();
		}

		return CEngine::GetInstance().GetSpriteManager().GetSpritePath(*mySprite);
	}
}
