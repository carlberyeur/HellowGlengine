#pragma once

class IEffect;

enum class eEffectType
{
	eSprite
};

class IEffectManager
{
public:
	IEffectManager();
	virtual ~IEffectManager();

	virtual CU::UniquePointer<IEffect> CreateEffect(const eEffectType aType) = 0;
};
