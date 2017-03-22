#pragma once

namespace wendy
{
	class CSprite;

	struct SSpriteDeleter
	{
		static void Destroy(CSprite* aSprite);
	};

	class CSpriteManager
	{
	public:
		CSpriteManager();
		~CSpriteManager();

		CU::UniquePointer<CSprite, SSpriteDeleter> CreateSprite(const std::string& aSpritePath);
		CU::UniquePointer<CSprite, SSpriteDeleter> CopySprite(const CSprite& aSprite);
		void DestroySprite(CSprite* aSprite);

		void CollectGarbage();

	private:
		std::mutex myDeleteSpritesLock;
		CU::GrowingArray<CSprite*> mySprites;
		CU::GrowingArray<CSprite*> myDeadSprites;
	};
}
