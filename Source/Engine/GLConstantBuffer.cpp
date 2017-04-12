#include "stdafx.h"
#include "GLConstantBuffer.h"
#include "OpenGLExtensions.h"

namespace wendy
{
	CGLUniformInt::CGLUniformInt(const int aUniformLocation)
		: myUniformLocation(aUniformLocation)
	{
	}

	CGLUniformInt::~CGLUniformInt()
	{
	}

	void CGLUniformInt::SetData(const int& aData)
	{
		glUniform1i(myUniformLocation, aData);
	}

	CGLUniformVec2::CGLUniformVec2(const int aUniformLocation)
		: myUniformLocation(aUniformLocation)
	{
	}

	CGLUniformVec2::~CGLUniformVec2()
	{
	}

	void CGLUniformVec2::SetData(const CU::Vector2f& aData)
	{
		glUniform2fv(myUniformLocation, 1, aData.vector);
	}


	CGLUniformVec3::CGLUniformVec3(const int aUniformLocation)
		: myUniformLocation(aUniformLocation)
	{
	}

	CGLUniformVec3::~CGLUniformVec3()
	{
	}

	void CGLUniformVec3::SetData(const CU::Vector3f& aData)
	{
		glUniform3fv(myUniformLocation, 1, aData.vector);
	}
	
	
	CGLUniformVec4::CGLUniformVec4(const int aUniformLocation)
		: myUniformLocation(aUniformLocation)
	{
	}
	
	CGLUniformVec4::~CGLUniformVec4()
	{
	}

	void CGLUniformVec4::SetData(const CU::Vector4f& aData)
	{
		glUniform4fv(myUniformLocation, 1, aData.vector);
	}
}
