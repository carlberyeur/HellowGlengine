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
	const std::string& GetLastError() const;

	static CU::UniquePointer<ITextureManager> Create(const IGraphicsFramework& aFramework);
	static CU::UniquePointer<ITextureManager> Create(const COpenGLFramework& aFramework);

protected:
	std::string myLastError;
};
