#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

CGameObject::CGameObject()
	: myComponents(4u)
	, myRotation(0.f)
{
}

CGameObject::CGameObject(const CGameObject& aOther)
	: myComponents(aOther.myComponents)
	, myRotation(aOther.myRotation)
{
	for (IComponent* component : aOther.myComponents)
	{
		IComponent* newComponent = component->Copy();
		newComponent->myParent = this;
		myComponents.Add(newComponent);
	}
}

CGameObject::CGameObject(CGameObject&& aOther)
	: myComponents(std::move(aOther.myComponents))
	, myRotation(aOther.myRotation)
{
	for (IComponent* component : myComponents)
	{
		component->myParent = this;
	}
}

CGameObject::~CGameObject()
{
	if (myComponents.IsInitialized())
	{
		myComponents.DeleteAll();
	}
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
	aComponent.myParent = this;
	myComponents.Add(&aComponent);
}

void CGameObject::NotifyComponents(const SComponentMessage& aMessage)
{
	for (IComponent* component : myComponents)
	{
		component->Recieve(aMessage);
	}
}

void CGameObject::Move(const CU::Vector2f aDisplacement)
{
	CU::Vector2f rotatedDisplacement = aDisplacement;
	
	rotatedDisplacement.x = aDisplacement.x * cosf(myRotation) - aDisplacement.y * sinf(myRotation);
	rotatedDisplacement.y = aDisplacement.x * sinf(myRotation) + aDisplacement.y * cosf(myRotation);

	SetPosition(GetPosition() + rotatedDisplacement);
}

void CGameObject::SetPosition(const CU::Vector2f aPosition)
{
	myPosition = aPosition;
}

void CGameObject::SetPosition(const float aPositionX, const float aPositionY)
{
	myPosition.Set(aPositionX, aPositionY);
}

CU::Vector2f CGameObject::GetPosition() const
{
	return myPosition;
}
