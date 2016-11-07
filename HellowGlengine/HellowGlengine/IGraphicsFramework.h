#pragma once
class IGraphicsFramework
{
public:
	IGraphicsFramework();
	virtual ~IGraphicsFramework();

	virtual bool Init() = 0;
	virtual void ClearFrame() = 0;
	virtual void Present() = 0;
	virtual void UpdateWindowSize() = 0;
};
