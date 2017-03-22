#pragma once
#include "IGraphicsFramework.h"

namespace wendy
{
	class IWindow;

	class COpenGLFramework : public IGraphicsFramework
	{
	public:
		COpenGLFramework();
		~COpenGLFramework();

		bool Init(IWindow& aWindow) override;
		void ClearFrame() override;
		void Present() override;
		void UpdateWindowSize() override;

		bool LoadExtensionList(void* aHwnd);

		CU::UniquePointer<IMeshManager> CreateMeshManager() const override;
		CU::UniquePointer<ITextureManager> CreateTextureManager() const override;
		CU::UniquePointer<IEffectManager> CreateEffectManager() const override;

	private:
		void* myDeviceContext;
		void* myRenderingContext;
	};
}
