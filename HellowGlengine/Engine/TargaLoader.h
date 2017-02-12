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
		eFailedReadingImageData
	};

	CTargaLoader();
	~CTargaLoader();

	static eLoadResult LoadTargaTexture(const std::string& aTexturePath, CU::GrowingArray<char>& aDataOut);
	static const std::string& GetLastError();

private:
	static std::string ourLastError;
};
