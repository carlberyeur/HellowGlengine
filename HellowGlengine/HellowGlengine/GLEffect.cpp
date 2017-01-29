#include "stdafx.h"
#include <fstream>

#include "GLEffect.h"
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
}

bool CGLEffect::Init(const std::string& aVertexShaderPath, const std::string& aGeometryShaderPath, const std::string& aPixelShaderPath, const unsigned int aInputLayoutFlags)
{
	std::ifstream vertexShaderFile(aVertexShaderPath, std::ios::binary);

	vertexShaderFile.seekg(0, vertexShaderFile.end);
	long long bytesOfFile = vertexShaderFile.tellg();

	CU::GrowingArray<char, long long> vertexBlob(bytesOfFile + 1);
	vertexBlob.Resize(bytesOfFile);

	vertexShaderFile.seekg(0, vertexShaderFile.beg);

	vertexShaderFile.read(vertexBlob.AsPointer(), bytesOfFile);
	vertexShaderFile.close();
	vertexBlob.Add('\0');

	myVertexShader = glCreateShader(GL_VERTEX_SHADER);
	char* vertexString = vertexBlob.AsPointer();
	glShaderSource(myVertexShader, 1, &vertexString, nullptr);

	glCompileShader(myVertexShader);

	int compileStatus = 0;
	glGetShaderiv(myVertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus != 1)
	{
		//error
		return false;
	}
}

void CGLEffect::Activate()
{
	//glUseProgram(myShaderProgram);
}
