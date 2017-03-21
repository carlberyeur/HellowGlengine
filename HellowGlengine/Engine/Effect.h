#pragma once

class IConstantBuffer;

template <typename T>
class CConstantBuffer;

class IEffect : public CU::IMemoryManagedObject
{
public:
	IEffect();
	virtual ~IEffect();

	virtual bool Init(const std::string& aVertexShaderPath, const std::string& aGeometryShaderPath, const std::string& aPixelShaderPath, const unsigned int aInputLayoutFlags) = 0;
	virtual void Activate() = 0;

	template <typename T>
	CConstantBuffer<T>* GetConstantBuffer(const std::string& aConstantBufferName);

protected:
	enum class eConstantBufferType
	{
		eInt,
		eVec2,
		eVec3,
	};

	virtual void* GetConstantBuffer(const eConstantBufferType aType, const std::string& aConstantBufferName) = 0;

	CU::GrowingArray<IConstantBuffer*> myConstantBuffers;
};

template<>
inline CConstantBuffer<int>* IEffect::GetConstantBuffer(const std::string& aConstantBufferName)
{
	return reinterpret_cast<CConstantBuffer<int>*>(GetConstantBuffer(eConstantBufferType::eInt, aConstantBufferName));
}

template<>
inline CConstantBuffer<CU::Vector2f>* IEffect::GetConstantBuffer(const std::string& aConstantBufferName)
{
	return reinterpret_cast<CConstantBuffer<CU::Vector2f>*>(GetConstantBuffer(eConstantBufferType::eVec2, aConstantBufferName));
}

template<>
inline CConstantBuffer<CU::Vector3f>* IEffect::GetConstantBuffer(const std::string& aConstantBufferName)
{
	return reinterpret_cast<CConstantBuffer<CU::Vector3f>*>(GetConstantBuffer(eConstantBufferType::eVec3, aConstantBufferName));
}
