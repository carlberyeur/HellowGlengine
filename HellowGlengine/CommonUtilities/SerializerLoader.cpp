#include "stdafx.h"
#include "SerializerLoader.h"

namespace CU
{
	CSerializerLoader::CSerializerLoader()
	{
	}

	CSerializerLoader::CSerializerLoader(const CU::GrowingArray<char>& aBuffer)
		: myBuffer(aBuffer)
	{
	}

	CSerializerLoader::CSerializerLoader(CU::GrowingArray<char>&& aBuffer)
		: myBuffer(std::move(aBuffer))
	{
	}

	CSerializerLoader::~CSerializerLoader()
	{
	}

	void CSerializerLoader::Init(const CU::GrowingArray<char>& aBuffer)
	{
		myBuffer = aBuffer;
	}

	void CSerializerLoader::Init(CU::GrowingArray<char>&& aBuffer)
	{
		myBuffer = std::move(aBuffer);
	}

	void CSerializerLoader::Cerealize(unsigned char& aChar)
	{
		myBuffer.RemoveChunk(&aChar, sizeof(char));
	}

	void CSerializerLoader::Cerealize(unsigned int& aUInt)
	{
		myBuffer.RemoveChunk(&aUInt, sizeof(unsigned int));
	}

	void CSerializerLoader::Cerealize(float& aFloat)
	{
		myBuffer.RemoveChunk(&aFloat, sizeof(float));
	}

	void CSerializerLoader::Cerealize(CU::Vector2f& aVector2f)
	{
		myBuffer.RemoveChunk(&aVector2f, sizeof(CU::Vector2f));
	}

	void CSerializerLoader::Cerealize(std::string& aString)
	{
		unsigned int stringLength = 0;
		Cerealize(stringLength);
		if (stringLength > 0)
		{
			aString.resize(stringLength);
			myBuffer.RemoveChunk(&aString[0], stringLength);
		}
	}
}
