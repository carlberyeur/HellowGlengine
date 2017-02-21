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
			glBindAttribLocation(myShaderProgram, i, inputAttributes[i].c_str());
		}
	}

	if (!LinkShader(myShaderProgram))
	{
		return false;
	}

	int samplerLocation = glGetUniformLocation(myShaderProgram, "albedoTexture");
	glUniform1i(samplerLocation, 0);

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
void output_error(unsigned shaderid, char* filename);

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
		output_error(aShaderIDOut, nullptr);
		//get error message
		//output error message
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
		//get error message
		//output error message
		return false;
	}

	return true;
}
#include <iostream>
void output_error(unsigned shaderId, char *)
{
	int logSize;
	char* infoLog;


	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	std::cout << infoLog << std::endl;

}
