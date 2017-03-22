#include "stdafx.h"
#include "SpriteComponent.h"
#include "../Engine/SpriteInstance.h"

CSpriteComponent::CSpriteComponent()
{
}

CSpriteComponent::CSpriteComponent(const std::string& aSpritePath)
{
	mySpriteInstance = new wendy::CSpriteInstance();
	mySpriteInstance->Init(aSpritePath);
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
	mySpriteInstance = CU::MakeUnique<wendy::CSpriteInstance>(*aCopy.mySpriteInstance);

	return *this;
}

IComponent* CSpriteComponent::Copy()
{
	CSpriteComponent* copy = new CSpriteComponent(*this);
	return copy;
}

void CSpriteComponent::Init()
{
	mySpriteInstance->SetPosition(GetParent()->GetPosition());
}

void CSpriteComponent::Render()
{
	mySpriteInstance->Render();
}
