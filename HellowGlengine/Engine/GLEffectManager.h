#pragma once
#include "EffectManager.h"

namespace wendy
{
	class CGLEffectManager : public IEffectManager
	{
	public:
		CGLEffectManager();
		~CGLEffectManager();

		CU::SharedPointer<IEffect> CreateEffect(const eEffectType aType) override;
	};
}
