#include "stdafx.h"
#include "PhysicsComponent.h"


CPhysicsComponent::CPhysicsComponent()
{
}

CPhysicsComponent::CPhysicsComponent(const CPhysicsComponent& aCopy)
{
}

CPhysicsComponent::~CPhysicsComponent()
{
}

CPhysicsComponent& CPhysicsComponent::operator=(const CPhysicsComponent& aCopy)
{
	aCopy;
	return *this;
}

void CPhysicsComponent::Update(const CU::Time aDeltaTime)
{
	aDeltaTime;
}

void CPhysicsComponent::Recieve(const SComponentMessage& aMessage)
{
	aMessage;
}

bool CPhysicsComponent::Answer(SComponentMessage& aMessage)
{
	aMessage;
	return false;
}

IComponent* CPhysicsComponent::Copy()
{
	return new CPhysicsComponent(*this);
}

bool CPhysicsComponent::Load(CU::ISerializer& aSerializer)
{
	aSerializer;
	return true;
}

bool CPhysicsComponent::Save(CU::ISerializer& aSerializer)
{
	aSerializer;
	return true;
}

void CPhysicsComponent::Init()
{
}
