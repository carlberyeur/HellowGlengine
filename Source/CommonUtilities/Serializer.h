#pragma once

namespace CU
{
	class ISerializer
	{
	public:
		ISerializer() {}
		virtual ~ISerializer() {}

		virtual void Cerealize(unsigned char& aChar) = 0;
		virtual void Cerealize(unsigned short& aShort) = 0;
		virtual void Cerealize(unsigned int& aUInt) = 0;
		virtual void Cerealize(int& aInt) = 0;
		virtual void Cerealize(float& aFloat) = 0;
		virtual void Cerealize(double& aDouble) = 0;
		virtual void Cerealize(CU::Vector2f& aVector2f) = 0;
		virtual void Cerealize(CU::Vector3f& aVector3f) = 0;
		virtual void Cerealize(CU::Vector4f& aVector4f) = 0;
		virtual void Cerealize(CU::Matrix33f& aMatrix33f) = 0;
		virtual void Cerealize(CU::Matrix44f& aMatrix44f) = 0;
		virtual void Cerealize(std::string& aString) = 0;

		template<typename ENUM>
		void Cerealize(ENUM& aEnum);

		static CU::GrowingArray<char> ReadFile(const std::string& aFilePath);
		static bool WriteFile(const CU::GrowingArray<char>& aBuffer, const std::string& aFilePath);
	};

	template<typename ENUM, unsigned int SIZE>
	struct SEnumSerializer;

	template<typename ENUM>
	struct SEnumSerializer<ENUM, 1>
	{
		static void Cerealize(ENUM& aEnum, ISerializer& aSerializer)
		{
			unsigned char* byteEnum = reinterpret_cast<unsigned char*>(&aEnum);
			aSerializer.Cerealize(*byteEnum);
		}
	};

	template<typename ENUM>
	struct SEnumSerializer<ENUM, 2>
	{
		static void Cerealize(ENUM& aEnum, ISerializer& aSerializer)
		{
			unsigned short* shortEnum = reinterpret_cast<unsigned short*>(&aEnum);
			aSerializer.Cerealize(*shortEnum);
		}
	};

	template<typename ENUM>
	struct SEnumSerializer<ENUM, 4>
	{
		static void Cerealize(ENUM& aEnum, ISerializer& aSerializer)
		{
			unsigned int* longEnum = reinterpret_cast<unsigned int*>(&aEnum);
			aSerializer.Cerealize(*longEnum);
		}
	};

	template<typename ENUM>
	inline void ISerializer::Cerealize(ENUM& aEnum)
	{
		SEnumSerializer<ENUM, sizeof(aEnum)>::Cerealize(aEnum, *this);
	}
}
