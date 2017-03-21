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

CSprite::CSprite(CSprite& aCopy)
	: CSprite()
{
	CEngine& engine = CEngine::GetInstance();

	myMesh = engine.GetMeshManager().CreateQuad();

	myTexture = std::move(aCopy.myTexture);

	myEffect = engine.GetEffectManager().CreateEffect(eEffectType::eSprite);

	myPositionSlot = myEffect->GetConstantBuffer<CU::Vector3f>("spritePosition");
	mySizeSlot = myEffect->GetConstantBuffer<CU::Vector2f>("spriteSize");
	myTextureSlot = myEffect->GetConstantBuffer<int>("albedoTexture");
}

CSprite::~CSprite()
{
}

void CSprite::Init(const std::string& aTexturePath)
{
	CEngine& engine = CEngine::GetInstance();

	myMesh = engine.GetMeshManager().CreateQuad();

	ITexture* tex = nullptr;
	CEngine::GetInstance().GetTextureManager().LoadTexture(aTexturePath, tex);
	myTexture = CU::UniquePointer<ITexture>(tex);

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
