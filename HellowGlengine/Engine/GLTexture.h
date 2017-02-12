#pragma once
#include "Texture.h"

class CGLTexture : public ITexture
{
public:
	enum class eLoadResult
	{
		eSuccess,
		eInvalidTextureUnit,
		eNoPixelData
	};

	CGLTexture();
	~CGLTexture();

	eLoadResult Init(const unsigned int aTextureUnit, const void* aPixelData);

private:
	unsigned int myTextureID;
};

