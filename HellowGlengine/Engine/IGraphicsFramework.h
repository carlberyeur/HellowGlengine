#pragma once

class IWindow;
class IMeshManager;
class ITextureManager;
class IEffectManager;

class IGraphicsFramework
{
public:
	IGraphicsFramework();
	virtual ~IGraphicsFramework();

	virtual bool Init(IWindow& aWindow) = 0;
	virtual void ClearFrame() = 0;
	virtual void Present() = 0;
	virtual void UpdateWindowSize() = 0;

	virtual CU::UniquePointer<ITextureManager> CreateTextureManager() const = 0;
	virtual CU::UniquePointer<IMeshManager> CreateMeshManager() const = 0;
	virtual CU::UniquePointer<IEffectManager> CreateEffectManager() const = 0;
};
