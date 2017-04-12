#pragma once
#include "RenderPackage.h"

namespace wendy
{
	class CGLRenderPackage : public IRenderPackage
	{
	public:
		CGLRenderPackage();
		~CGLRenderPackage();

		virtual bool Init(const CU::Vector2ui aSize) override;
		virtual void Clear(const CU::Vector4f aClearColor = CU::Vector4f::Zero) override;
		virtual void Activate() override;
		virtual CU::Vector2ui GetSize() override;

	private:
		CU::Vector4ui myViewPort;
		unsigned int myFrameBuffer;
		unsigned int myTexture;
		unsigned int myDepthBuffer;
	};
}
