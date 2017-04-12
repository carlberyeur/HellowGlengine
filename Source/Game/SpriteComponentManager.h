#pragma once

class IComponent;
class CSpriteComponent;

class CSpriteComponentManager
{
public:
	friend class CComponentManager;

	CSpriteComponent* CreateSpriteComponent();
	IComponent* CreateComponent();

private:
	CSpriteComponentManager(CComponentManager& aComponentManager);
	~CSpriteComponentManager();

	CU::GrowingArray<CSpriteComponent> mySpriteComponents;
	CComponentManager& myComponentManager;
};
