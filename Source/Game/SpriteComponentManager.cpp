#include "stdafx.h"
#include "SpriteComponentManager.h"
#include "SpriteComponent.h"

#include "ComponentManager.h"

CSpriteComponent* CSpriteComponentManager::CreateSpriteComponent()
{
	if (mySpriteComponents.Size() >= mySpriteComponents.Capacity())
	{
		DL_MESSAGE_BOX("out of memory in sprite component manager. capacity: %u", mySpriteComponents.Capacity());
		return nullptr;
	}

	mySpriteComponents.Add();
	CSpriteComponent& newSprite = mySpriteComponents.GetLast();


	return &newSprite;
}

IComponent* CSpriteComponentManager::CreateComponent()
{
	return CreateSpriteComponent();
}

CSpriteComponentManager::CSpriteComponentManager(CComponentManager& aComponentManager)
	: mySpriteComponents(64u)
	, myComponentManager(aComponentManager)
{
}

CSpriteComponentManager::~CSpriteComponentManager()
{
}
