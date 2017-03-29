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
	return *this;
}

void CPhysicsComponent::Update(const CU::Time aDeltaTime)
{
}

void CPhysicsComponent::Recieve(const SComponentMessage& aMessage)
{
}

bool CPhysicsComponent::Answer(SComponentMessage& aMessage)
{
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
