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

CU::SharedPointer<IEffect> CGLEffectManager::CreateEffect(const eEffectType aType)
{
	CU::SharedPointer<IEffect> effect;

	switch (aType)
	{
	case eEffectType::eSprite:
		effect = new CGLEffect();
		effect->Init("Shaders/VS_", "", "Shaders/FS_", eInputLayout::eInputLayout_ePos | eInputLayout::eInputLayout_eTex);
		break;
	}

	return effect;
}
