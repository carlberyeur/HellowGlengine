#pragma once
#include "EffectManager.h"

class CGLEffectManager : public IEffectManager
{
public:
	CGLEffectManager();
	~CGLEffectManager();

	CU::SharedPointer<IEffect> CreateEffect(const eEffectType aType) override;
};
