#pragma once
#include "TextureManager.h"

class CGLTextureManager : public ITextureManager
{
public:
	CGLTextureManager();
	~CGLTextureManager();

	eLoadResult LoadTexture(const std::string& aTexturePath, ITexture*& aTexturePointerOut) override;

private:
	unsigned int myTextureUnit;
};

