#include "stdafx.h"
#include "Component.h"


IComponent::IComponent()
	: myParent(nullptr)
	, myID(-1)
{
}

IComponent::~IComponent()
{
}

void IComponent::Init()
{
}

void IComponent::Update(const CU::Time /*aDeltaTime*/)
{
}

void IComponent::Recieve(const SComponentMessage& /*aMessage*/)
{
}

bool IComponent::Answer(SComponentMessage& /*aMessage*/)
{
	return false;
}

CGameObject* IComponent::GetParent() /*const*/
{
	return myParent;
}

int IComponent::GetParentID()
{
	return myParent->GetID();
}

int IComponent::GetID() const
{
	return myID;
}
