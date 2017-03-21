#include "stdafx.h"
#include "Sprite.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "EffectManager.h"

#include "CConstantBuffer.h"

#include "Mesh.h"
#include "Effect.h"
#include "Texture.h"

CSprite::CSprite()
	: myPositionSlot(nullptr)
	, mySizeSlot(nullptr)
	, myTextureSlot(nullptr)
{
}

CSprite::CSprite(const CSprite& aCopy)
	: myMesh(aCopy.myMesh)
	, myTexture(aCopy.myTexture)
	, myEffect(aCopy.myEffect)
	, myPositionSlot(aCopy.myPositionSlot)
	, mySizeSlot(aCopy.mySizeSlot)
	, myTextureSlot(aCopy.myTextureSlot)
{
}

CSprite::~CSprite()
{
}

void CSprite::Init(const std::string& aTexturePath)
{
	CEngine& engine = CEngine::GetInstance();

	myMesh = engine.GetMeshManager().CreateQuad();

	ITextureManager::eLoadResult textureResult = ITextureManager::eLoadResult::eSuccess;
	myTexture = engine.GetTextureManager().LoadTexture(aTexturePath, textureResult);
	//error checking

	myEffect = engine.GetEffectManager().CreateEffect(eEffectType::eSprite);

	myPositionSlot = myEffect->GetConstantBuffer<CU::Vector3f>("spritePosition");
	mySizeSlot = myEffect->GetConstantBuffer<CU::Vector2f>("spriteSize");
	myTextureSlot = myEffect->GetConstantBuffer<int>("albedoTexture");
}

void CSprite::Render(const CU::Vector2f aPosition)
{
	myEffect->Activate();

	myTextureSlot->SetData(0);
	myPositionSlot->SetData(CU::Vector3f(aPosition, 0));
	mySizeSlot->SetData(myTexture->GetTextureSizeF() / CEngine::GetInstance().GetWindowSizeF());

	myTexture->SetTexture();

	myMesh->Render();
}
