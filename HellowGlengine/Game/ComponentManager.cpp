#include "stdafx.h"
#include "ComponentManager.h"
#include "SpriteComponentManager.h"

#include <new>

CComponentManager::CComponentManager()
{
	mySpriteComponentManager = new (mySpriteMemory.GetAddress()) CSpriteComponentManager(*this);
}

CComponentManager::~CComponentManager()
{
	delete (mySpriteMemory.GetAddress(), mySpriteComponentManager); //??????????????????
}

IComponent* CComponentManager::CreateComponent(const eComponentType aType)
{
	return nullptr;
}

IComponent* CComponentManager::GetComponent(const int aComponentID)
{
	return nullptr;
}
