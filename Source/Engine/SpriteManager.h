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

		std::string GetSpritePath(const CSprite& aSprite) const;

		void CollectGarbage();

	private:
		std::mutex myDeleteSpritesLock;
		std::map<std::string, int> mySpriteLookup;
		CU::GrowingArray<CSprite*, int> mySprites;
		CU::GrowingArray<CSprite*, int> myDeadSprites;
	};
}
