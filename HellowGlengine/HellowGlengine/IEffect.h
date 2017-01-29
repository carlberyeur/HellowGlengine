#pragma once

class IEffect
{
public:
	IEffect();
	virtual ~IEffect();

	virtual bool Init(const std::string& aVertexShaderPath, const std::string& aGeometryShaderPath, const std::string& aPixelShaderPath, const unsigned int aInputLayoutFlags) = 0;
	virtual void Activate() = 0;
};
