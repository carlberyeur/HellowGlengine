#pragma once
#include "../CommonUtilities/MemoryManagedObject.h"

class ITexture : public CU::IMemoryManagedObject
{
public:
	ITexture();
	virtual ~ITexture();

	virtual void SetTexture() = 0;

	inline CU::Vector2ui GetTextureSize() const;
	inline CU::Vector2f GetTextureSizeF() const;

protected:
	CU::Vector2ui myPixelSize;
};

inline CU::Vector2ui ITexture::GetTextureSize() const
{
	return myPixelSize;
}

inline CU::Vector2f ITexture::GetTextureSizeF() const
{
	return CU::Vector2f(myPixelSize);
}
