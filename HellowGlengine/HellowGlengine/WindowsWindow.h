#pragma once
#include "IOSWindow.h"

class CWindowsWindow : public IOSWindow
{
public:
	CWindowsWindow();
	~CWindowsWindow();

	bool Init(const SCreationParameters& aCreationParameters) override;
	void Update() override;

private:
	bool RegisterWindowsWindow(void* aHInstance);
	bool InitHWND(void* aHInstance, const unsigned int aWindowWidth, const unsigned int aWindowHeight);

	void* myHWND;
	void* myHInstance;
};
