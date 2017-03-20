#include "stdafx.h"
#include <fstream>
#include <sstream>

#include "GLEffect.h"
#include "EInputLayout.h"
#include "OpenGLExtensions.h"

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
			glBindAttribLocation(myShaderProgram, i, inputAttributes[i].c_str());//kolla att de stämmer överens
		}
	}

	if (!LinkShader(myShaderProgram))
	{
		return false;
	}

	//myTextureLocation = glGetUniformLocation(myShaderProgram, "albedoTexture");
	//
	//if (myTextureLocation == -1)
	//{
	//	return false;
	//}

	//myPositionLocation = glGetUniformLocation(myShaderProgram, "spritePosition");

	//if (myPositionLocation == -1)
	//{
	//	//return false;
	//}

	//mySizeLocation = glGetUniformLocation(myShaderProgram, "spriteSize");

	//if (mySizeLocation == -1)
	//{
	//	return false;
	//}

	return true;
}

void CGLEffect::Activate()
{
	glUseProgram(myShaderProgram);

	//if (myTextureLocation != -1)
	//{
	//	glUniform1i(myTextureLocation, 0);
	//}

	//if (myPositionLocation != -1)
	//{
	//	float position[3] = { 0.5f, 0.5f, 0.f };
	//	glUniform3fv(myPositionLocation, 1, position);
	//	std::bind(glUniform3fv, myPositionLocation, 1, position);
	//}

	//if (mySizeLocation != -1)
	//{
	//	float size[2] = { 256.f / 1920.f, 256.f / 1080.f };
	//	glUniform2fv(mySizeLocation, 1, size);
	//}
}

std::function<void(int)> CGLEffect::BindUniformInt(const std::string& aUniformName) const
{
	int intLocation = glGetUniformLocation(myShaderProgram, aUniformName.c_str());

	if (intLocation == -1)
	{
		return std::function<void(int)>();
	}

	return std::bind(glUniform1i, intLocation, std::placeholders::_1);
}

std::function<void(CU::Vector2f)> CGLEffect::BindUniformVector2(const std::string& aUniformName) const
{
	int vectorLocation = glGetUniformLocation(myShaderProgram, aUniformName.c_str());

	if (vectorLocation == -1)
	{
		return std::function<void(CU::Vector2f)>();
	}

	return [vectorLocation](CU::Vector2f aVector2) { glUniform2fv(vectorLocation, 1, aVector2.vector); };
}

std::function<void(const CU::Vector3f&)> CGLEffect::BindUniformVector3(const std::string& aUniformName) const
{
	int vectorLocation = glGetUniformLocation(myShaderProgram, aUniformName.c_str());

	if (vectorLocation == -1)
	{
		return std::function<void(const CU::Vector3f&)>();
	}

	return [vectorLocation](const CU::Vector3f& aVector3) { glUniform3fv(vectorLocation, 1, aVector3.vector); };
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
