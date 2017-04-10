#pragma once
#include "Window.h"

typedef struct HWND__ *HWND;
typedef struct HINSTANCE__ *HINSTANCE;

namespace wendy
{
	class CWindowsWindow : public IWindow
	{
	public:
		CWindowsWindow();
		~CWindowsWindow();

		bool Init(const SCreationParameters& aCreationParameters) override;
		void Update() override;
		bool LoadExtensionList(class COpenGLFramework& aOpenGLFrameWork) override;
		bool InitInputWrapper(CInputManager& aInputManager) override;
		virtual void* DeviceContext() override;

		inline HWND GetHWND() const;
		inline HINSTANCE GetHInstance() const;

	private:
		bool RegisterWindowsWindow(HINSTANCE aHInstance);
		bool InitHWND(void* aHInstance, const unsigned int aWindowWidth, const unsigned int aWindowHeight);

		HINSTANCE myHInstance;
		HWND myHWND;
	};

	inline HINSTANCE CWindowsWindow::GetHInstance() const
	{
		return myHInstance;
	}

	inline HWND CWindowsWindow::GetHWND() const
	{
		return myHWND;
	}
}
