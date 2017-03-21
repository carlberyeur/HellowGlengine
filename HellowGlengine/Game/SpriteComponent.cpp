#include "stdafx.h"
#include "SpriteComponent.h"
#include "../Engine/SpriteInstance.h"

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

CSpriteComponent& CSpriteComponent::operator=(const CSpriteComponent& aCopy)
{
	mySpriteInstance = CU::MakeUnique<CSpriteInstance>(*aCopy.mySpriteInstance);

	return *this;
}

IComponent* CSpriteComponent::Copy()
{
	CSpriteComponent* copy = new CSpriteComponent(*this);
	return copy;
}

void CSpriteComponent::Render()
{
	mySpriteInstance->Render();
}
