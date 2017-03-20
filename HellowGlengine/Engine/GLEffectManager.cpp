#include "stdafx.h"
#include "GLEffectManager.h"
#include "GLEffect.h"

#include "EInputLayout.h"

CGLEffectManager::CGLEffectManager()
{
}

CGLEffectManager::~CGLEffectManager()
{
}

CU::UniquePointer<IEffect> CGLEffectManager::CreateEffect(const eEffectType aType)
{
	CU::UniquePointer<IEffect> effect;

	switch (aType)
	{
	case eEffectType::eSprite:
		effect = CU::MakeUnique<CGLEffect>();
		effect->Init("Shaders/VS_", "", "Shaders/FS_", eInputLayout::eInputLayout_ePos | eInputLayout::eInputLayout_eTex);
		break;
	}

	return effect;
}
