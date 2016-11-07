#pragma once

class IOSWindow;
class IGraphicsFramework;

class CEngine
{
public:
	struct SCreationParameters
	{
		enum eCreationFlags
		{
			eGL = 1 << 0,
			eDX = 1 << 1,
			eFullScreen = 1 << 2,
			eWindows = 1 << 3,
			eLinux = 1 << 4
		};

		unsigned int myWindowHeight;
		unsigned int myWindowWidth;
		unsigned int myCreationFlags;
		//unsigned int myDebugFlags;
	};

	static bool CreateInstance(const SCreationParameters& aCreationParameters);
	static void DestroyInstance();
	static CEngine& GetInstance();

	void Start();
	void Shutdown();

private:
	CEngine();
	~CEngine();

	bool InternalInit(const SCreationParameters& aCreationParameters);

	IOSWindow* myWindow;
	IGraphicsFramework* myGraphicsFramework;

	static CEngine* ourInstance;
};
