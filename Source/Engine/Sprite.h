#pragma once

namespace wendy
{
	struct STextureRect;

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
		void Render(const CU::Vector2f aPosition, const CU::Vector2f aScale, const STextureRect& aTextureRect);
		CU::Vector2f GetTextureSize() const;

		inline int AddRef();
		inline int DecRef();

	private:
		CU::SharedPointer<IMesh> myMesh;
		CU::SharedPointer<ITexture> myTexture;
		CU::SharedPointer<IEffect> myEffect;

		CConstantBuffer<CU::Vector3f>* myPositionSlot;
		CConstantBuffer<CU::Vector2f>* mySizeSlot;
		CConstantBuffer<int>* myTextureSlot;
		CConstantBuffer<CU::Vector4f>* myTextureRectSlot;

		int myRefCount;
	};

	inline int wendy::CSprite::AddRef()
	{
		return ++myRefCount;
	}

	inline int CSprite::DecRef()
	{
		return --myRefCount;
	}
}
