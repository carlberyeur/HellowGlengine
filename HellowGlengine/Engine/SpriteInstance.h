#pragma once

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

		CU::Vector2f GetSize() const;

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
