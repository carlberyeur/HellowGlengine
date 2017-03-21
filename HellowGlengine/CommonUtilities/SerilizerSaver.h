#pragma once
#include "Serializer.h"

namespace CU
{
	class CSerializerSaver : public ISerializer
	{
	public:
		CSerializerSaver(const unsigned int aBufferStartSize = 32);
		~CSerializerSaver();

		void Cerealize(unsigned char& aChar) override;
		void Cerealize(unsigned int& aUInt) override;
		void Cerealize(float& aFloat) override;
		void Cerealize(double& aDouble) override;
		void Cerealize(CU::Vector2f& aVector2f) override;
		void Cerealize(CU::Vector3f& aVector3f) override;
		void Cerealize(CU::Vector4f& aVector4f) override;
		void Cerealize(CU::Matrix33f& aMatrix33f) override;
		void Cerealize(CU::Matrix44f& aMatrix44f) override;
		void Cerealize(std::string& aString) override;

		const CU::GrowingArray<char>& GetBuffer() const;

	private:
		CU::GrowingArray<char> myBuffer;
	};
}
