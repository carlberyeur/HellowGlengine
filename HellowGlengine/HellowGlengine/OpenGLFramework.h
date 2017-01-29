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

	bool LoadExtensionList(void* aHwnd);

private:
	void* myDeviceContext;
	void* myRenderingContext;
};
