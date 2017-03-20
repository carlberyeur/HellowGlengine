#include "stdafx.h"
#include "Effect.h"
#include "IConstantBuffer.h"

IEffect::IEffect()
	: myConstantBuffers(2)
{
}

IEffect::~IEffect()
{
	myConstantBuffers.DeleteAll();
}
