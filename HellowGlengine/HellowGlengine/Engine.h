#pragma once

class IOSWindow;
class IGraphicsFramework;

class CEngine
{
public:
	struct CreationParameters
	{
		unsigned int myWindowHeight;
		unsigned int myWindowWidth;
	};

	static bool CreateInstance(const CreationParameters& aCreationParameters);
	static void DestroyInstance();
	static CEngine& GetInstance();

	void Start();
	void Shutdown();

private:
	IOSWindow* myWindow;
	IGraphicsFramework* myGraphicsFramework;

	CEngine();
	~CEngine();

	bool InternalInit(const CreationParameters& aCreationParameters);

	static CEngine* ourInstance;
};
