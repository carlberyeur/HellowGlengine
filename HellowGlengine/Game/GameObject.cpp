#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

CGameObject::CGameObject()
	: myComponents(4u)
{
}

CGameObject::CGameObject(const CGameObject& aOther)
{
	*this = aOther;
}

CGameObject::CGameObject(CGameObject&& aOther)
{
	*this = std::move(aOther);
}

CGameObject::~CGameObject()
{
	myComponents.DeleteAll();
}

CGameObject& CGameObject::operator=(const CGameObject& aOther)
{
	myComponents.DeleteAll();

	for (IComponent* component : aOther.myComponents)
	{
		IComponent* newComponent = component->Copy();
		newComponent->myParent = this;
		myComponents.Add(newComponent);
	}

	return *this;
}

CGameObject& CGameObject::operator=(CGameObject&& aOther)
{
	myComponents = std::move(aOther.myComponents);

	for (IComponent* component : myComponents)
	{
		component->myParent = this;
	}

	return *this;
}

void CGameObject::Init()
{
	for (IComponent* component : myComponents)
	{
		component->Init();
	}
}

void CGameObject::AddComponent(IComponent& aComponent)
{
	myComponents.Add(&aComponent);
}

void CGameObject::NotifyComponents(const SComponentMessage& aMessage)
{
	for (IComponent* component : myComponents)
	{
		component->Recieve(aMessage);
	}
}
