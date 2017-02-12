#include "stdafx.h"
#include "GLTextureManager.h"
#include "GLTexture.h"

#include "TargaLoader.h"

CGLTextureManager::CGLTextureManager()
	: myTextureUnit(0u)
{
}

CGLTextureManager::~CGLTextureManager()
{
}

ITextureManager::eLoadResult CGLTextureManager::LoadTexture(const std::string& aTexturePath, ITexture*& aTexturePointerOut)
{
	if (aTexturePath.empty() || !aTexturePointerOut)
	{
		return eLoadResult::eInvalidArgument;
	}

	CU::GrowingArray<char> data;
	CTargaLoader::eLoadResult result = CTargaLoader::LoadTargaTexture(aTexturePath, data);
	if (result != CTargaLoader::eLoadResult::eSuccess)
	{
		//HandleTargaError(result, CTargaLoader::GetLastError());
	}

	CGLTexture* newTexture = new CGLTexture();
	newTexture->Init(myTextureUnit++, data.AsVoidPointer());

	return eLoadResult::eSuccess;
}
