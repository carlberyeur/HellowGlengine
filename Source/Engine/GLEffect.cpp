#include "stdafx.h"
#include <fstream>
#include <sstream>

#include "GLEffect.h"
#include "GLConstantBuffer.h"
#include "EInputLayout.h"
#include "OpenGLExtensions.h"

namespace wendy
{
	CGLEffect::CGLEffect()
		: myVertexShader(0u)
		, myGeometryShader(0u)
		, myFragmentShader(0u)
		, myShaderProgram(0u)
	{
		myTextureLocation = -1;
		myPositionLocation = -1;
		mySizeLocation = -1;
	}

	CGLEffect::~CGLEffect()
	{
		glDetachShader(myShaderProgram, myVertexShader);
		glDetachShader(myShaderProgram, myFragmentShader);

		glDeleteShader(myVertexShader);
		glDeleteShader(myFragmentShader);

		glDeleteProgram(myShaderProgram);
	}

	bool CGLEffect::Init(const std::string& aVertexShaderPath, const std::string& aGeometryShaderPath, const std::string& aPixelShaderPath, const unsigned int aInputLayoutFlags)
	{
		CU::GrowingArray<std::string> inputAttributes(4u);
		std::string shaderFilePath;
		bool hasInputAttributes = GetInputLayout(aInputLayoutFlags, inputAttributes, shaderFilePath);

		std::string vertexShaderString;
		if (!ReadShaderFile(aVertexShaderPath + shaderFilePath, vertexShaderString))
		{
			//must have vertex shader, return false
			return false;
		}

		std::string geometryShaderString;
		if (!aGeometryShaderPath.empty() && !ReadShaderFile(aGeometryShaderPath + shaderFilePath, geometryShaderString))
		{
			return false;
		}

		std::string fragmentShaderString;
		if (!aPixelShaderPath.empty() && !ReadShaderFile(aPixelShaderPath + shaderFilePath, fragmentShaderString))
		{
			return false;
		}

		if (!CompileShader(vertexShaderString, GL_VERTEX_SHADER, myVertexShader))
		{
			return false;
		}

		if (!geometryShaderString.empty() && !CompileShader(geometryShaderString, GL_FRAGMENT_SHADER, myGeometryShader))
		{
			return false;
		}

		if (!fragmentShaderString.empty() && !CompileShader(fragmentShaderString, GL_FRAGMENT_SHADER, myFragmentShader))
		{
			return false;
		}

		myShaderProgram = glCreateProgram();

		glAttachShader(myShaderProgram, myVertexShader);

		if (myFragmentShader)
		{
			glAttachShader(myShaderProgram, myFragmentShader);
		}

		if (myGeometryShader)
		{
			glAttachShader(myShaderProgram, myGeometryShader);
		}

		if (hasInputAttributes)
		{
			for (unsigned int i = 0; i < inputAttributes.Size(); ++i)
			{
				glBindAttribLocation(myShaderProgram, i, inputAttributes[i].c_str());//kolla att de st�mmer �verens
			}
		}

		if (!LinkShader(myShaderProgram))
		{
			return false;
		}

		return true;
	}

	void CGLEffect::Activate()
	{
		glUseProgram(myShaderProgram);
	}

	bool CGLEffect::GetInputLayout(const unsigned int aInputLayoutFlags, CU::GrowingArray<std::string>& aAttributes, std::string& aShaderFilePath)
	{
		if (!aInputLayoutFlags)
		{
			return false;
		}

		if (aInputLayoutFlags & eInputLayout::eInputLayout_ePos)
		{
			aAttributes.Add("Pos");
			aShaderFilePath += aAttributes.GetLast();
		}
		if (aInputLayoutFlags & eInputLayout::eInputLayout_eTex)
		{
			aAttributes.Add("Tex");
			aShaderFilePath += aAttributes.GetLast();
		}

		aShaderFilePath += ".glsl";

		return !aAttributes.Empty();
	}

	bool CGLEffect::ReadShaderFile(const std::string& aShaderPath, std::string& aFileContentOut)
	{
		std::ifstream vertexShaderFile(aShaderPath);
		if (!vertexShaderFile.good())
		{
			//DL_MESSAGEBOX();
			return false;
		}

		std::stringstream vertexShaderContent;
		vertexShaderContent << vertexShaderFile.rdbuf();
		aFileContentOut = vertexShaderContent.str();

		return !aFileContentOut.empty();
	}

	bool CGLEffect::CompileShader(const std::string& aFileContent, const unsigned int aShaderStage, unsigned int& aShaderIDOut)
	{
		aShaderIDOut = glCreateShader(aShaderStage);
		const char* shaderString = aFileContent.c_str();
		glShaderSource(aShaderIDOut, 1, &shaderString, nullptr);

		glCompileShader(aShaderIDOut);

		int compileStatus = 0;
		glGetShaderiv(aShaderIDOut, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus != 1)
		{
			int logSize = 0;
			std::string infoLog;
			glGetShaderiv(aShaderIDOut, GL_INFO_LOG_LENGTH, &logSize);
			infoLog.resize(logSize + 1);
			glGetShaderInfoLog(aShaderIDOut, logSize, nullptr, &infoLog[0]);
			DL_MESSAGE_BOX("Failed to compile shader: %s", infoLog.c_str());
			return false;
		}

		return true;
	}

	bool CGLEffect::LinkShader(const unsigned int aShaderProgram)
	{
		glLinkProgram(aShaderProgram);

		int linkStatus = 0;
		glGetProgramiv(aShaderProgram, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != 1)
		{
			int logSize = 0;
			std::string infoLog;
			glGetProgramiv(aShaderProgram, GL_INFO_LOG_LENGTH, &logSize);
			infoLog.resize(logSize + 1);
			glGetProgramInfoLog(aShaderProgram, logSize, nullptr, &infoLog[0]);
			DL_MESSAGE_BOX("Failed to link shader: %s", infoLog.c_str());
			return false;
		}

		return true;
	}

	void* CGLEffect::GetConstantBuffer(const eConstantBufferType aType, const std::string& aConstantBufferName)
	{
		int location = glGetUniformLocation(myShaderProgram, aConstantBufferName.c_str());

		if (location == -1)
		{
			return nullptr;
		}

		IConstantBuffer* constantBuffer = nullptr;

		switch (aType)
		{
		case IEffect::eConstantBufferType::eInt:
			constantBuffer = new CGLUniformInt(location);
			break;
		case IEffect::eConstantBufferType::eVec2:
			constantBuffer = new CGLUniformVec2(location);
			break;
		case IEffect::eConstantBufferType::eVec3:
			constantBuffer = new CGLUniformVec3(location);
			break;
		case IEffect::eConstantBufferType::eVec4:
			constantBuffer = new CGLUniformVec4(location);
			break;
		default:
			return nullptr;
		}

		myConstantBuffers.Add(constantBuffer);

		return constantBuffer;
	}
}
