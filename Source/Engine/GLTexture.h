#pragma once
#include "Texture.h"

namespace wendy
{
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

		eLoadResult Init(const unsigned int aTextureUnit, const void* aPixelData, const CU::Vector2ui& aTextureSize);
		eLoadResult Init(const unsigned int aTextureUnit, std::nullptr_t, const CU::Vector2ui& aTextureSize);
		void SetTexture() override;

	private:
		unsigned int myTextureID;
	};
}
