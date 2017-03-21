#pragma once

class IMesh;
class ITexture;
class IEffect;

template <typename T>
class CConstantBuffer;

class CSprite
{
public:
	CSprite();
	CSprite(CSprite& aCopy);
	~CSprite();

	void Init(const std::string& aTexturePath);
	void Render(const CU::Vector2f aPosition);

private:
	std::function<void(const CU::Vector3f&)> mySetPositionUniform;
	std::function<void(CU::Vector2f)> mySetSizeUniform;

	CConstantBuffer<CU::Vector3f>* myPositionSlot;
	CConstantBuffer<CU::Vector2f>* mySizeSlot;
	CConstantBuffer<int>* myTextureSlot;

	CU::UniquePointer<IMesh> myMesh;
	CU::UniquePointer<ITexture> myTexture;
	CU::UniquePointer<IEffect> myEffect;
};
