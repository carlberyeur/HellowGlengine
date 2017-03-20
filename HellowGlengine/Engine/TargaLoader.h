#pragma once

class CTargaLoader
{
public:
	enum class eLoadResult
	{
		eSuccess,
		eInvalidPath,
		eFailedReadingHeader,
		eBPPNot32,
		eImageSizeZero,
		eFailedReadingImageData
	};

	static eLoadResult LoadTargaTexture(const std::string& aTexturePath, CU::GrowingArray<char>& aDataOut, CU::Vector2ui& aTextureSizeOut);
	static const std::string& GetLastError();

private:
	static std::string ourLastError;
};
