#pragma once

#include "InputListener.h"

namespace CU
{
	class Time;
	class CStopWatch;
}

class IWindow;
class IGraphicsFramework;

class IMeshManager;
class ITextureManager;
class IEffectManager;
class CInputManager;

class CEngine : public IInputListener
{
public:
	struct SCreationParameters
	{
		enum eCreationFlags : unsigned int
		{
			eGL = 1 << 0,
			eDX = 1 << 1,
			eFullScreen = 1 << 2,
			eWindows = 1 << 3,
			eLinux = 1 << 4
		};

		std::function<void(void)> myInitCallback;
		std::function<bool(const CU::Time)> myUpdateCallback;
		std::function<void(void)> myRenderCallback;

		unsigned int myWindowHeight;
		unsigned int myWindowWidth;
		unsigned int myCreationFlags;
		//unsigned int myDebugFlags;
	};

	static bool CreateInstance(const SCreationParameters& aCreationParameters);
	static void DestroyInstance();
	static CEngine& GetInstance();
	static CEngine* GetInstancePtr();

	void Start();
	void Shutdown();

	void Update();
	void Render();

	inline IGraphicsFramework& GetGraphicsFramework();
	inline ITextureManager& GetTextureManager();
	
	inline CU::Vector2ui GetWindowSize() const;
	inline CU::Vector2f GetWindowSizeF() const;

private:
	CEngine();
	~CEngine();

	bool InternalInit(const SCreationParameters& aCreationParameters);
	eResult TakeInput(const CInputMessage& aMessage) override;

	std::function<void(void)> myInitCallback;
	std::function<bool(const CU::Time)> myUpdateCallback;
	std::function<void(void)> myRenderCallback;

	CU::UniquePointer<IWindow> myWindow;
	CU::UniquePointer<IGraphicsFramework> myGraphicsFramework;

	//CU::UniquePointer<IMeshManager> myMeshManager;
	CU::UniquePointer<ITextureManager> myTextureManager;
	//CU::UniquePointer<IEffectManager> myEffectManager;
	CU::UniquePointer<CInputManager> myInputManager;

	CU::UniquePointer<CU::CStopWatch> myLogicTimer;
	CU::UniquePointer<CU::CStopWatch> myRenderTimer;

	CU::Vector2ui myWindowSize;

	static CEngine* ourInstance;
};

inline IGraphicsFramework& CEngine::GetGraphicsFramework()
{
	return *myGraphicsFramework;
}

inline ITextureManager& CEngine::GetTextureManager()
{
	return *myTextureManager;
}

inline CU::Vector2ui CEngine::GetWindowSize() const
{
	return myWindowSize;
}

inline CU::Vector2f CEngine::GetWindowSizeF() const
{
	return CU::Vector2f(myWindowSize);
}
