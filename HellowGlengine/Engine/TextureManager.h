#pragma once

class ITexture;

class ITextureManager
{
public:
	enum  class eLoadResult
	{
		eSuccess,
		eFileNotFound,
		eInvalidArgument,
		eFailedLoadingFile
	};

	ITextureManager();
	virtual ~ITextureManager();

	virtual eLoadResult LoadTexture(const std::string& aTexturePath, ITexture*& aTexturePointerOut) = 0;
	const std::string& GetLastError() const;

protected:
	std::string myLastError;
};
