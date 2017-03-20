#pragma once
#include "IEffect.h"

class CGLEffect : public IEffect
{
public:
	CGLEffect();
	CGLEffect(const CGLEffect&) = delete;
	~CGLEffect();

	bool Init(const std::string& aVertexShaderPath, const std::string& aGeometryShaderPath, const std::string& aPixelShaderPath, const unsigned int aInputLayoutFlags) override;
	void Activate() override;

	std::function<void(int)> BindUniformInt(const std::string& aUniformName) const;
	std::function<void(CU::Vector2f)> BindUniformVector2(const std::string& aUniformName) const;
	std::function<void(const CU::Vector3f&)> BindUniformVector3(const std::string& aUniformName) const;

private:
	static bool GetInputLayout(const unsigned int aInputLayoutFlags, CU::GrowingArray<std::string>& aAttributes, std::string& aShaderFilePath);
	static bool ReadShaderFile(const std::string& aShaderPath, std::string& aFileContentOut);
	static bool CompileShader(const std::string& aFileContent, const unsigned int aShaderStage, unsigned int& aShaderIDOut);
	static bool LinkShader(const unsigned int aShaderProgram);

	unsigned int myVertexShader;
	unsigned int myGeometryShader;
	unsigned int myFragmentShader;
	unsigned int myShaderProgram;

	int myTextureLocation;
	int myPositionLocation;
	int mySizeLocation;
};
