#include "stdafx.h"
#include "Effect.h"
#include "IConstantBuffer.h"

namespace wendy
{
	IEffect::IEffect()
		: myConstantBuffers(2)
	{
	}

	IEffect::~IEffect()
	{
		myConstantBuffers.DeleteAll();
	}
}
