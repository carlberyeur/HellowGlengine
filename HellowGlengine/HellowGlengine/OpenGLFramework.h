#pragma once
#include "IGraphicsFramework.h"

class COpenGLFramework : public IGraphicsFramework
{
public:
	COpenGLFramework();
	~COpenGLFramework();

	bool Init() override;
	void ClearFrame() override;
	void Present() override;
	void UpdateWindowSize() override;

private:
	bool LoadExtensionList();

	void* myDeviceContext;
	void* myRenderingContext;
};
