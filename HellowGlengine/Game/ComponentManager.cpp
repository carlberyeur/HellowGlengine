#include "stdafx.h"
#include "ComponentManager.h"
#include "Component.h"
#include "ComponentType.h"

#include "SpriteComponentManager.h"

#include <new>

CComponentManager::CComponentManager()
	: myComponents(1024)
{
	mySpriteComponentManager = new (mySpriteMemory.GetAddress()) CSpriteComponentManager(*this);
}

CComponentManager::~CComponentManager()
{
	mySpriteComponentManager->~CSpriteComponentManager();
}

IComponent* CComponentManager::CreateComponent(const eComponentType aType)
{
	IComponent* newComponent = nullptr;

	switch (aType)
	{
	case eComponentType::eSpriteComponent:
		newComponent = mySpriteComponentManager->CreateComponent();
		break;
	}

	if (newComponent)
	{
		newComponent->myID = myComponents.Size();
		myComponents.Add(newComponent);
	}

	return newComponent;
}

IComponent* CComponentManager::GetComponent(const int aComponentID)
{
	if (myComponents.HasIndex(aComponentID))
	{
		return myComponents[aComponentID];
	}

	return nullptr;
}
