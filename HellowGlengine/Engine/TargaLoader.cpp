#include "stdafx.h"
#include "TargaLoader.h"

struct TargaHeader
{
	unsigned char data1[12];
	unsigned short width;
	unsigned short height;
	unsigned char bpp;
	unsigned char data2;
};

std::string CTargaLoader::ourLastError("");

CTargaLoader::CTargaLoader()
{
}

CTargaLoader::~CTargaLoader()
{
}

CTargaLoader::eLoadResult CTargaLoader::LoadTargaTexture(const std::string& aTexturePath, CU::GrowingArray<char>& aDataOut)
{
	if (aTexturePath.empty()) return eLoadResult::eInvalidPath;

	std::ifstream targaFile(aTexturePath, std::ifstream::binary);
	if (!targaFile.good())
	{
		return eLoadResult::eInvalidPath;
	}
	
	TargaHeader targaFileHeader;

	if (!targaFile.read(reinterpret_cast<char*>(&targaFileHeader), sizeof(TargaHeader)).good())
	{
		return eLoadResult::eFailedReadingHeader;
	}

	if (targaFileHeader.bpp != 32)
	{
		return eLoadResult::eBPPNot32;
	}

	unsigned int imageSize = targaFileHeader.width * targaFileHeader.height * 4u;
	aDataOut.Init(imageSize);
	aDataOut.Resize(imageSize);

	if (!targaFile.read(aDataOut.AsPointer(), imageSize).good())
	{
		return eLoadResult::eFailedReadingImageData;
	}

	targaFile.close();

	return eLoadResult::eSuccess;
}

const std::string& CTargaLoader::GetLastError()
{
	return ourLastError;
}
