#include "stdafx.h"
#include "TextureManager.h"

namespace wendy
{
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
}
