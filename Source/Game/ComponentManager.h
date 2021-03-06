#pragma once

class IComponent;
class CSpriteComponentManager;

enum class eComponentType;

class CComponentManager
{
public:
	CComponentManager();
	~CComponentManager();

	IComponent* CreateComponent(const eComponentType aType);
	IComponent* GetComponent(const int aComponentID);

	static CComponentManager* GetInstance();

private:
	CU::CMemoryBlob<24, CSpriteComponentManager> mySpriteMemory;

	CU::GrowingArray<IComponent*, int> myComponents;

	CSpriteComponentManager* mySpriteComponentManager;

	static CComponentManager* ourInstance;
};
