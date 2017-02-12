#pragma once
#include "../CommonUtilities/MemoryManagedObject.h"

class ITexture : public CU::IMemoryManagedObject
{
public:
	ITexture();
	virtual ~ITexture();

	inline CU::Vector2ui GetTextureSize() const;

protected:
	CU::Vector2ui myPixelSize;
};

inline CU::Vector2ui ITexture::GetTextureSize() const
{
	return myPixelSize;
}
