#pragma once
#include "IGraphicsFramework.h"

class IOSWindow;

class COpenGLFramework : public IGraphicsFramework
{
public:
	COpenGLFramework();
	~COpenGLFramework();

	bool Init(IOSWindow& aWindow) override;
	void ClearFrame() override;
	void Present() override;
	void UpdateWindowSize() override;

private:
	bool LoadExtensionList(void* aHwnd);

	void* myDeviceContext;
	void* myRenderingContext;
};
