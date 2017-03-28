#include "stdafx.h"
#include "SpriteComponent.h"
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

bool CSpriteComponent::Serialize(CU::ISerializer& aSerializer)
{
	//TODO: spara eller hämta filepath, om hämta: skapa ny sprite
	std::string filePath;
	if (mySpriteInstance.IsValid())
	{
		filePath = mySpriteInstance->GetFilePath();
	}
	bool isLoading = filePath.empty();
	aSerializer.Cerealize(filePath);
	isLoading = isLoading && !filePath.empty();
	if (isLoading)
	{
		mySpriteInstance = CU::MakeUnique<wendy::CSpriteInstance>();
		mySpriteInstance->Init(filePath);
	}
	return true;
}
