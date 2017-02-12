#include "stdafx.h"
#include "TextureManager.h"


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
