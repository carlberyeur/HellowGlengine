#pragma once

namespace wendy
{
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

		virtual CU::SharedPointer<IEffect> CreateEffect(const eEffectType aType) = 0;
	};
}
