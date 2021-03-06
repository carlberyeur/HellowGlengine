#include "stdafx.h"
#include "SerializerSaver.h"

namespace CU
{
	CSerializerSaver::CSerializerSaver()
	{
	}

	CSerializerSaver::CSerializerSaver(const unsigned int aBufferStartSize)
	{
		Init(aBufferStartSize);
	}

	CSerializerSaver::~CSerializerSaver()
	{
	}

	void CSerializerSaver::Init(const unsigned int aBufferStartSize)
	{
		assert(aBufferStartSize > 0 && "incoming heap corruption");
		myBuffer.Init(aBufferStartSize);
	}

	void CSerializerSaver::Cerealize(unsigned char& aChar)
	{
		myBuffer.Add(static_cast<char>(aChar));
	}

	void CSerializerSaver::Cerealize(unsigned short& aShort)
	{
		myBuffer.AddChunk(&aShort, sizeof(unsigned short));
	}

	void CSerializerSaver::Cerealize(unsigned int& aUInt)
	{
		myBuffer.AddChunk(&aUInt, sizeof(unsigned int));
	}

	void CSerializerSaver::Cerealize(int& aInt)
	{
		myBuffer.AddChunk(&aInt, sizeof(int));
	}

	void CSerializerSaver::Cerealize(float& aFloat)
	{
		myBuffer.AddChunk(&aFloat, sizeof(float));
	}

	void CSerializerSaver::Cerealize(double& aDouble)
	{
		myBuffer.AddChunk(&aDouble, sizeof(aDouble));
	}

	void CSerializerSaver::Cerealize(CU::Vector2f& aVector2f)
	{
		myBuffer.AddChunk(&aVector2f, sizeof(CU::Vector2f));
	}

	void CSerializerSaver::Cerealize(CU::Vector3f& aVector3f)
	{
		myBuffer.AddChunk(&aVector3f, sizeof(CU::Vector3f));
	}

	void CSerializerSaver::Cerealize(CU::Vector4f& aVector4f)
	{
		myBuffer.AddChunk(&aVector4f, sizeof(CU::Vector4f));
	}

	void CSerializerSaver::Cerealize(CU::Matrix33f& aMatrix33f)
	{
		myBuffer.AddChunk(&aMatrix33f, sizeof(CU::Matrix33f));
	}

	void CSerializerSaver::Cerealize(CU::Matrix44f& aMatrix44f)
	{
		myBuffer.AddChunk(&aMatrix44f, sizeof(CU::Matrix44f));
	}

	void CSerializerSaver::Cerealize(std::string& aString)
	{
		unsigned int stringLength = static_cast<unsigned int>(aString.size());
		Cerealize(stringLength);
		myBuffer.AddChunk(aString.c_str(), stringLength);
	}

	const CU::GrowingArray<char>& CSerializerSaver::GetBuffer() const
	{
		return myBuffer;
	}

	bool CSerializerSaver::WriteFile(const std::string& aFilePath) const
	{
		return ISerializer::WriteFile(myBuffer, aFilePath);
	}
}
