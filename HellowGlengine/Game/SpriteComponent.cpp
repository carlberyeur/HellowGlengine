#include "stdafx.h"
#include "SpriteComponent.h"


CSpriteComponent::CSpriteComponent()
{
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& aCopy)
{
	*this = aCopy;
}

CSpriteComponent::~CSpriteComponent()
{
}

CSpriteComponent& CSpriteComponent::operator=(const CSpriteComponent& /*aCopy*/)
{
	//copy data here

	return *this;
}

IComponent* CSpriteComponent::Copy()
{
	CSpriteComponent* copy = new CSpriteComponent(*this);
	return copy;
}
