#include "stdafx.h"
#include "SpriteComponent.h"

#include "ComponentManager.h"

#include "../Engine/SpriteInstance.h"
#include "../CommonUtilities/Serializer.h"

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

bool CSpriteComponent::Load(CU::ISerializer& aSerializer)
{
	std::string filePath;

	aSerializer.Cerealize(filePath);

	mySpriteInstance = CU::MakeUnique<wendy::CSpriteInstance>();
	mySpriteInstance->Init(filePath);
	return true;
}

bool CSpriteComponent::Save(CU::ISerializer& aSerializer)
{
	unsigned char componentType = static_cast<unsigned char>(/*eComponentType::eSprite*/0);
	aSerializer.Cerealize(componentType);
	
	std::string filePath = mySpriteInstance->GetFilePath();
	aSerializer.Cerealize(filePath);
	return true;
}
