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
	CSprite(const CSprite& aCopy);
	~CSprite();

	void Init(const std::string& aTexturePath);
	void Render(const CU::Vector2f aPosition);

private:
	CU::SharedPointer<IMesh> myMesh;
	CU::SharedPointer<ITexture> myTexture;
	CU::SharedPointer<IEffect> myEffect;

	CConstantBuffer<CU::Vector3f>* myPositionSlot;
	CConstantBuffer<CU::Vector2f>* mySizeSlot;
	CConstantBuffer<int>* myTextureSlot;
};
