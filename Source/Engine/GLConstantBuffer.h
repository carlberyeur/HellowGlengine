#pragma once
#include "CConstantBuffer.h"

namespace wendy
{
	class CGLUniformInt : public CConstantBuffer<int>
	{
	public:
		CGLUniformInt(const int aUniformLocation);
		~CGLUniformInt();

		void SetData(const int& aData) override;

	private:
		int myUniformLocation;
	};

	class CGLUniformVec2 : public CConstantBuffer<CU::Vector2f>
	{
	public:
		CGLUniformVec2(const int aUniformLocation);
		~CGLUniformVec2();

		void SetData(const CU::Vector2f& aData) override;

	private:
		int myUniformLocation;
	};

	class CGLUniformVec3 : public CConstantBuffer<CU::Vector3f>
	{
	public:
		CGLUniformVec3(const int aUniformLocation);
		~CGLUniformVec3();

		void SetData(const CU::Vector3f& aData) override;

	private:
		int myUniformLocation;
	};

	class CGLUniformVec4 : public CConstantBuffer<CU::Vector4f>
	{
	public:
		CGLUniformVec4(const int aUniformLocation);
		~CGLUniformVec4();

		void SetData(const CU::Vector4f& aData) override;

	private:
		int myUniformLocation;
	};
}
