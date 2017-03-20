#include "stdafx.h"
#include "TextureManager.h"
#include "GLTextureManager.h"

ITextureManager::ITextureManager()
{
}

ITextureManager::~ITextureManager()
{
}

const std::string& ITextureManager::GetLastError() const
{
	return myLastError;
}

CU::UniquePointer<ITextureManager> ITextureManager::Create(const IGraphicsFramework& aFramework)
{
	return aFramework.CreateTextureManager();
}

CU::UniquePointer<ITextureManager> ITextureManager::Create(const COpenGLFramework&)
{
	return CU::MakeUnique<CGLTextureManager>();
}
