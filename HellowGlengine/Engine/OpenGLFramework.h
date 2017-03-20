#pragma once
#include "IGraphicsFramework.h"

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

	CU::UniquePointer<ITextureManager> CreateTextureManager() const override;

private:
	void* myDeviceContext;
	void* myRenderingContext;
};
