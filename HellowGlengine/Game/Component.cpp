#include "stdafx.h"
#include "Component.h"


IComponent::IComponent()
	: myParent(nullptr)
{
}

IComponent::~IComponent()
{
}

void IComponent::Init()
{
}

void IComponent::Recieve(const SComponentMessage& /*aMessage*/)
{
}

CGameObject* IComponent::GetParent()
{
	return myParent;
}
