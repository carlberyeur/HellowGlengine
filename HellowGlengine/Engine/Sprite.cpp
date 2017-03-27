#include "stdafx.h"
#include "Sprite.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "EffectManager.h"

#include "CConstantBuffer.h"

#include "Mesh.h"
#include "Effect.h"
#include "Texture.h"
#include "TextureRect.h"

namespace wendy
{
	CSprite::CSprite()
		: myPositionSlot(nullptr)
		, mySizeSlot(nullptr)
		, myTextureSlot(nullptr)
		, myTextureRectSlot(nullptr)
	{
	}

	CSprite::CSprite(const CSprite& aCopy)
		: myMesh(aCopy.myMesh)
		, myTexture(aCopy.myTexture)
		, myEffect(aCopy.myEffect)
		, myPositionSlot(aCopy.myPositionSlot)
		, mySizeSlot(aCopy.mySizeSlot)
		, myTextureSlot(aCopy.myTextureSlot)
		, myTextureRectSlot(aCopy.myTextureRectSlot)
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
		myTextureRectSlot = myEffect->GetConstantBuffer<CU::Vector4f>("textureRect");
	}

	void CSprite::Render(const CU::Vector2f aPosition, const STextureRect& aTextureRect)
	{
		myEffect->Activate();

		myTextureSlot->SetData(0);
		myTextureRectSlot->SetData(aTextureRect.AsVector4f());
		myPositionSlot->SetData(CU::Vector3f(aPosition, 0));
		mySizeSlot->SetData(myTexture->GetTextureSizeF() / CEngine::GetInstance().GetWindowSizeF());

		myTexture->SetTexture();

		myMesh->Render();
	}

	CU::Vector2f CSprite::GetTextureSize() const
	{
		if (myTexture.IsValid())
		{
			return myTexture->GetTextureSizeF();
		}

		return CU::Vector2f::Zero;
	}
}
