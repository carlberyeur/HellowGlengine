#pragma once

namespace wendy
{
	struct SSpriteDeleter;
	class CSprite;

	class CSpriteInstance
	{
	public:
		CSpriteInstance();
		CSpriteInstance(const CSpriteInstance& aCopy);
		~CSpriteInstance();

		void Init(const std::string& aTexturePath);
		void Render();

		inline void SetPosition(const CU::Vector2f aPosition);
		inline CU::Vector2f GetPosition() const;

	private:
		CU::Vector2f myPosition;
		CU::UniquePointer<CSprite, SSpriteDeleter> mySprite;
	};

	inline void CSpriteInstance::SetPosition(const CU::Vector2f aPosition)
	{
		myPosition = aPosition;
	}

	inline CU::Vector2f CSpriteInstance::GetPosition() const
	{
		return myPosition;
	}
}
