#include "stdafx.h"
#include "GLTextureManager.h"
#include "GLTexture.h"

#include "TargaLoader.h"

namespace wendy
{
	CGLTextureManager::CGLTextureManager()
		: myTextureUnit(0u)
	{
	}

	CGLTextureManager::~CGLTextureManager()
	{
	}

	ITextureManager::eLoadResult CGLTextureManager::LoadTexture(const std::string& aTexturePath, ITexture*& aTexturePointerOut)
	{
		if (aTexturePath.empty())
		{
			return eLoadResult::eInvalidArgument;
		}

		CU::Vector2ui textureSize;
		CU::GrowingArray<char> data;
		CTargaLoader::eLoadResult result = CTargaLoader::LoadTargaTexture(aTexturePath, data, textureSize);
		if (result != CTargaLoader::eLoadResult::eSuccess)
		{
			//HandleTargaError(result, CTargaLoader::GetLastError());
			return eLoadResult::eFailedLoadingFile;
		}

		CGLTexture* newTexture = new CGLTexture();
		newTexture->Init(myTextureUnit, data.AsVoidPointer(), textureSize);
		aTexturePointerOut = newTexture;

		return eLoadResult::eSuccess;
	}

	CU::SharedPointer<ITexture> CGLTextureManager::LoadTexture(const std::string& aTexturePath, eLoadResult& aLoadResultOut)
	{
		CU::SharedPointer<ITexture> texture;

		if (aTexturePath.empty())
		{
			aLoadResultOut = eLoadResult::eInvalidArgument;
			return texture;
		}

		CU::Vector2ui textureSize;
		CU::GrowingArray<char> data;
		CTargaLoader::eLoadResult result = CTargaLoader::LoadTargaTexture(aTexturePath, data, textureSize);
		if (result != CTargaLoader::eLoadResult::eSuccess)
		{
			//HandleTargaError(result, CTargaLoader::GetLastError());
			aLoadResultOut = eLoadResult::eFailedLoadingFile;
			return texture;
		}

		CGLTexture* newTexture = new CGLTexture();
		if (newTexture->Init(myTextureUnit, data.AsVoidPointer(), textureSize) != CGLTexture::eLoadResult::eSuccess)
		{
			return texture;
		}

		texture = newTexture;

		aLoadResultOut = eLoadResult::eSuccess;

		return texture;
	}
}
