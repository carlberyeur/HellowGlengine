#pragma once

#include "IConstantBuffer.h"

template <typename T>
class CConstantBuffer : public IConstantBuffer
{
public:
	CConstantBuffer() {}
	virtual ~CConstantBuffer() {}

	virtual void SetData(const T& aData) = 0;
};
