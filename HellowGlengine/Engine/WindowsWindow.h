#pragma once
#include "IOSWindow.h"

class CWindowsWindow : public IOSWindow
{
public:
	CWindowsWindow();
	~CWindowsWindow();

	bool Init(const SCreationParameters& aCreationParameters) override;
	void Update() override;
	bool LoadExtensionList(class COpenGLFramework& aOpenGLFrameWork) override;
	bool InitInputWrapper(CInputManager& aInputManager) override;

	inline void* GetHWND() const;
	inline void* GetHInstance() const;

private:
	bool RegisterWindowsWindow(void* aHInstance);
	bool InitHWND(void* aHInstance, const unsigned int aWindowWidth, const unsigned int aWindowHeight);

	void* myHWND;
	void* myHInstance;
};

inline void* CWindowsWindow::GetHWND() const
{
	return myHWND;
}

inline void* CWindowsWindow::GetHInstance() const
{
	return myHInstance;
}
