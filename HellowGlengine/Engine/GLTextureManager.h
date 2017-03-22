#pragma once
#include "TextureManager.h"

namespace wendy
{
	class CGLTextureManager : public ITextureManager
	{
	public:
		CGLTextureManager();
		~CGLTextureManager();

		eLoadResult LoadTexture(const std::string& aTexturePath, ITexture*& aTexturePointerOut) override;
		CU::SharedPointer<ITexture> LoadTexture(const std::string& aTexturePath, eLoadResult& aLoadResultOut) override;

	private:
		unsigned int myTextureUnit;
	};
}
