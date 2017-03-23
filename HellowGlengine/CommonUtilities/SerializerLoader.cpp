#include "stdafx.h"
#include "SerializerLoader.h"

namespace CU
{
	CSerializerLoader::CSerializerLoader()
		: myPointer(0)
	{
	}

	CSerializerLoader::CSerializerLoader(const unsigned int aBufferStartSize)
		: CSerializerLoader()
	{
		assert(myBuffer.Capacity() > 0 && "incoming heap corruption");
		if (aBufferStartSize > 0)
		{
			myBuffer.Init(aBufferStartSize);
		}
	}

	CSerializerLoader::~CSerializerLoader()
	{
	}

	void CSerializerLoader::Init(const unsigned int aBufferStartSize)
	{
		assert(myBuffer.Capacity() > 0 && "incoming heap corruption");
		if (aBufferStartSize > 0)
		{
			myBuffer.Init(aBufferStartSize);
		}
	}

	void CSerializerLoader::Cerealize(unsigned char& aChar)
	{
		memcpy(&aChar, myBuffer.AsPointer(myPointer), sizeof(char));
		myPointer += sizeof(char);
	}

	void CSerializerLoader::Cerealize(unsigned int& aUInt)
	{
		memcpy(&aUInt, myBuffer.AsPointer(myPointer), sizeof(unsigned int));
		myPointer += sizeof(unsigned int);
	}

	void CSerializerLoader::Cerealize(float& aFloat)
	{
		memcpy(&aFloat, myBuffer.AsPointer(myPointer), sizeof(float));
		myPointer += sizeof(float);
	}

	void CSerializerLoader::Cerealize(double & aDouble)
	{
		memcpy(&aDouble, myBuffer.AsPointer(myPointer), sizeof(double));
		myPointer += sizeof(double);
	}

	void CSerializerLoader::Cerealize(CU::Vector2f& aVector2f)
	{
		memcpy(&aVector2f, myBuffer.AsPointer(myPointer), sizeof(CU::Vector2f));
		myPointer += sizeof(CU::Vector2f);
	}

	void CSerializerLoader::Cerealize(CU::Vector3f& aVector3f)
	{
		memcpy(&aVector3f, myBuffer.AsPointer(myPointer), sizeof(CU::Vector3f));
		myPointer += sizeof(CU::Vector3f);
	}

	void CSerializerLoader::Cerealize(CU::Vector4f& aVector4f)
	{
		memcpy(&aVector4f, myBuffer.AsPointer(myPointer), sizeof(CU::Vector4f));
		myPointer += sizeof(CU::Vector4f);
	}

	void CSerializerLoader::Cerealize(CU::Matrix33f& aMatrix33f)
	{
		memcpy(&aMatrix33f, myBuffer.AsPointer(myPointer), sizeof(CU::Matrix33f));
		myPointer += sizeof(CU::Matrix33f);
	}

	void CSerializerLoader::Cerealize(CU::Matrix44f& aMatrix44f)
	{
		memcpy(&aMatrix44f, myBuffer.AsPointer(myPointer), sizeof(CU::Matrix44f));
		myPointer += sizeof(CU::Matrix44f);
	}

	void CSerializerLoader::Cerealize(std::string& aString)
	{
		unsigned int stringLength = 0;
		Cerealize(stringLength);
		if (stringLength > 0)
		{
			aString.resize(stringLength);
			memcpy(&aString[0], myBuffer.AsPointer(myPointer), stringLength);
			myPointer += stringLength;
		}
	}

	const CU::GrowingArray<char>& CSerializerLoader::GetBuffer() const
	{
		return myBuffer;
	}

	bool CSerializerLoader::ReadFile(const std::string& aFilePath)
	{
		myBuffer = ISerializer::ReadFile(aFilePath);
		return myBuffer.IsInitialized();
	}
}
