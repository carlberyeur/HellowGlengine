#pragma once

class CSpriteComponent;

class CSpriteComponentManager
{
public:
	friend class CComponentManager;


private:
	CSpriteComponentManager(CComponentManager& aComponentManager);
	~CSpriteComponentManager();

	CU::GrowingArray<CSpriteComponent> mySpriteComponents;
	CComponentManager& myComponentManager;
};
