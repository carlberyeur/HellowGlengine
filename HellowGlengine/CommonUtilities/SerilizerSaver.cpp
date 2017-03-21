#include "stdafx.h"
#include "SerilizerSaver.h"

namespace CU
{
	CSerilizerSaver::CSerilizerSaver(const unsigned int aBufferStartSize)
		: myBuffer(aBufferStartSize)
	{
		assert(myBuffer.Capacity() > 0 && "incoming heap corruption");
	}

	CSerilizerSaver::~CSerilizerSaver()
	{
	}

	void CSerilizerSaver::Cerealize(unsigned char& aChar)
	{
		myBuffer.Add(aChar);
	}

	void CSerilizerSaver::Cerealize(unsigned int& aUInt)
	{
		myBuffer.AddChunk(&aUInt, sizeof(unsigned int));
	}

	void CSerilizerSaver::Cerealize(float& aFloat)
	{
		myBuffer.AddChunk(&aFloat, sizeof(float));
	}

	void CSerilizerSaver::Cerealize(CU::Vector2f& aVector2f)
	{
		myBuffer.AddChunk(&aVector2f, sizeof(CU::Vector2f));
	}

	void CSerilizerSaver::Cerealize(std::string& aString)
	{
		unsigned int stringLength = static_cast<unsigned int>(aString.size());
		Cerealize(stringLength);
		myBuffer.AddChunk(aString.c_str(), stringLength);
	}
}
