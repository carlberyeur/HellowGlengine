#pragma once
#include "Serializer.h"

namespace CU
{
	class CSerializerLoader : public ISerializer
	{
	public:
		CSerializerLoader();
		CSerializerLoader(const CU::GrowingArray<char>& aBuffer);
		CSerializerLoader(CU::GrowingArray<char>&& aBuffer);
		~CSerializerLoader();

		void Init(const CU::GrowingArray<char>& aBuffer);
		void Init(CU::GrowingArray<char>&& aBuffer);

		void Cerealize(unsigned char& aChar) override;
		void Cerealize(unsigned int& aChar) override;
		void Cerealize(float& aFloat) override;
		void Cerealize(CU::Vector2f& aVector2f) override;
		void Cerealize(std::string& aString) override;

	private:
		CU::GrowingArray<char> myBuffer;
	};
}
