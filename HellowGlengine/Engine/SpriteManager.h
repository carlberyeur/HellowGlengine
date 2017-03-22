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
		void DestroySprite(CSprite* aSprite);

		void CollectGarbage();

	private:
		std::mutex myDeleteSpritesLock;
		CU::GrowingArray<CSprite*> mySprites;
		CU::GrowingArray<CSprite*> myDeadSprites;
	};
}
