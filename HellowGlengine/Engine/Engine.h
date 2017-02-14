#pragma once

#include "InputListener.h"

namespace CU
{
	class Time;
	class CStopWatch;
}

class IOSWindow;
class IGraphicsFramework;
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
		std::function<void(const CU::Time)> myUpdateCallback;
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

private:
	CEngine();
	~CEngine();

	bool InternalInit(const SCreationParameters& aCreationParameters);

	std::function<void(void)> myInitCallback;
	std::function<void(const CU::Time)> myUpdateCallback;
	std::function<void(void)> myRenderCallback;

	IOSWindow* myWindow;
	IGraphicsFramework* myGraphicsFramework;

	CInputManager* myInputManager;

	CU::CStopWatch* myLogicTimer;
	CU::CStopWatch* myRenderTimer;

	static CEngine* ourInstance;

	eResult TakeInput(const CInputMessage& aMessage) override;
};
