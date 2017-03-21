#pragma once

class ITexture;
class IGraphicsFramework;
class COpenGLFramework;

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
	virtual CU::SharedPointer<ITexture> LoadTexture(const std::string& aTexturePath, eLoadResult& aLoadResultOut) = 0;
	const std::string& GetLastError() const;

protected:
	std::string myLastError;
};
