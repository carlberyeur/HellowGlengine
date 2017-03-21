#pragma once

namespace CU
{
	class ISerializer
	{
	public:
		ISerializer() {}
		virtual ~ISerializer() {}

		virtual void Cerealize(unsigned char& aChar) = 0;
		virtual void Cerealize(unsigned int& aUInt) = 0;
		virtual void Cerealize(float& aFloat) = 0;
		virtual void Cerealize(double& aDouble) = 0;
		virtual void Cerealize(CU::Vector2f& aVector2f) = 0;
		virtual void Cerealize(CU::Vector3f& aVector3f) = 0;
		virtual void Cerealize(CU::Vector4f& aVector4f) = 0;
		virtual void Cerealize(CU::Matrix33f& aMatrix33f) = 0;
		virtual void Cerealize(CU::Matrix44f& aMatrix44f) = 0;
		virtual void Cerealize(std::string& aString) = 0;

		static CU::GrowingArray<char> ReadFile(const std::string& aFilePath);
		static bool WriteFile(const CU::GrowingArray<char>& aBuffer, const std::string& aFilePath);
	};
}
