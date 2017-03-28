#pragma once

class CSpriteComponentManager
{
public:
	friend class CComponentManager;


private:
	CSpriteComponentManager(CComponentManager& aComponentManager);
	~CSpriteComponentManager();

	CComponentManager& myComponentManager;
};
