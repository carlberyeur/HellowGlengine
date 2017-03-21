#pragma once
#include "Serializer.h"

namespace CU
{
	class CSerilizerSaver : public ISerializer
	{
	public:
		CSerilizerSaver(const unsigned int aBufferStartSize = 32);
		~CSerilizerSaver();

		void Cerealize(unsigned char& aChar) override;
		void Cerealize(unsigned int& aUInt) override;
		void Cerealize(float& aFloat) override;
		void Cerealize(CU::Vector2f& aVector2f) override;
		void Cerealize(std::string& aString) override;

	private:
		CU::GrowingArray<char> myBuffer;
	};
}
