#pragma once

class IMesh;
class ITexture;
class IEffect;

class CGLSprite
{
public:
	CGLSprite();
	~CGLSprite();

	void Render(const CU::Vector2f aPosition);

private:
	std::function<void(const CU::Vector3f&)> mySetPositionUniform;
	std::function<void(CU::Vector2f)> mySetSizeUniform;
	std::function<void(int)> mySetTextureUniform;

	CU::UniquePointer<IMesh> myMesh;
	CU::UniquePointer<ITexture> myTexture;
	CU::UniquePointer<IEffect> myEffect;
};
