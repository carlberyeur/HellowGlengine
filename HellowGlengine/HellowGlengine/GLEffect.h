#pragma once
#include "IEffect.h"

class CGLEffect : public IEffect
{
public:
	CGLEffect();
	~CGLEffect();

	bool Init(const std::string& aVertexShaderPath, const std::string& aGeometryShaderPath, const std::string& aPixelShaderPath, const unsigned int aInputLayoutFlags) override;
	void Activate() override;

private:
	unsigned int myVertexShader;
	unsigned int myGeometryShader;
	unsigned int myFragmentShader;
	unsigned int myShaderProgram;
};
