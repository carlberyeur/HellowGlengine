#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "..\CommonUtilities\Serializer.h"

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

bool CGameObject::AskComponents(SComponentMessage& aMessage)
{
	for (IComponent* component : myComponents)
	{
		if (component->Answer(aMessage))
		{
			return true;
		}
	}

	return false;
}

void CGameObject::Update(const CU::Time aDeltaTime)
{
	for (IComponent* component : myComponents)
	{
		component->Update(aDeltaTime);
	}
}

void CGameObject::Move(const CU::Vector2f aDisplacement)
{
	CU::Vector2f rotatedDisplacement = aDisplacement;
	
	rotatedDisplacement.x = aDisplacement.x * cosf(myRotation) - aDisplacement.y * sinf(myRotation);
	rotatedDisplacement.y = aDisplacement.x * sinf(myRotation) + aDisplacement.y * cosf(myRotation);

	SetPosition(GetPosition() + rotatedDisplacement);
}

void CGameObject::Rotate(const float aRotation)
{
	myRotation += aRotation;

	constexpr float TAU_CONSTANT = 3.141592f * 2.f;
	while (myRotation > TAU_CONSTANT)
	{
		myRotation -= TAU_CONSTANT;
	}
}

void CGameObject::SetPosition(const CU::Vector2f aPosition)
{
	myPosition = aPosition;
}

void CGameObject::SetPosition(const float aPositionX, const float aPositionY)
{
	myPosition.Set(aPositionX, aPositionY);
}

void CGameObject::SetRotation(const float aRotation)
{
	myRotation = aRotation;
}

CU::Vector2f CGameObject::GetPosition() const
{
	return myPosition;
}

float CGameObject::GetRotation() const
{
	return myRotation;
}

#include "../CommonUtilities/SerilizerSaver.h"
#include "../CommonUtilities/SerializerLoader.h"

bool CGameObject::Save()
{
	CU::CSerializerSaver serializer(1024);

	serializer.Cerealize(myPosition);
	serializer.Cerealize(myRotation);
	
	unsigned int componentCount = myComponents.Size();
	serializer.Cerealize(componentCount);
	
	for (IComponent* component : myComponents)
	{
		component->Save(serializer);
	}

	return true;
}

bool CGameObject::Load()
{
	CU::CSerializerLoader serializer(1024);

	serializer.Cerealize(myPosition);
	serializer.Cerealize(myRotation);

	unsigned int componentCount = myComponents.Size();
	serializer.Cerealize(componentCount);

	myComponents.Init(componentCount);
	//CComponentManager::Load(serializer);
	for (IComponent* component : myComponents)
	{
		component->Load(serializer);
	}


	return true;
}
