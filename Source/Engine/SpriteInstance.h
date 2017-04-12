#pragma once

#include "TextureRect.h"

namespace wendy
{
	struct SSpriteDeleter;
	class CSprite;

	class CSpriteInstance
	{
	public:
		CSpriteInstance();
		CSpriteInstance(CSpriteInstance&& aCopy);
		CSpriteInstance(const CSpriteInstance& aCopy);
		~CSpriteInstance();

		CSpriteInstance& operator=(CSpriteInstance&& aCopy);
		CSpriteInstance& operator=(const CSpriteInstance& aCopy);

		void Init(const std::string& aTexturePath);
		void Render();

		std::string GetFilePath() const;
		CU::Vector2f GetSize() const;
		void SetVirtualSize(const CU::Vector2ui aVirtualPixelSize);

		inline void SetTextureRect(const STextureRect& aTextureRect);
		inline void SetPosition(const CU::Vector2f aPosition);
		inline void SetPosition(const float aX, const float aY);
		inline CU::Vector2f GetPosition() const;

	private:
		STextureRect myTextureRect;
		CU::Vector2f myPosition;
		CU::Vector2f myScale;
		CU::UniquePointer<CSprite, SSpriteDeleter> mySprite;
	};

	inline void CSpriteInstance::SetTextureRect(const STextureRect& aTextureRect)
	{
		myTextureRect = aTextureRect;
	}

	inline void CSpriteInstance::SetPosition(const CU::Vector2f aPosition)
	{
		myPosition = aPosition;
	}

	inline void CSpriteInstance::SetPosition(const float aX, const float aY)
	{
		myPosition.Set(aX, aY);
	}

	inline CU::Vector2f CSpriteInstance::GetPosition() const
	{
		return myPosition;
	}
}
