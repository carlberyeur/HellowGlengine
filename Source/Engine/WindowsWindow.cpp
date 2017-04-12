#include "stdafx.h"
#include "WindowsWindow.h"
#include "InputManager.h"
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

const wchar_t szWindowClass[] = L"OpenGL testing";
const wchar_t szTitle[] = L"HellopenGL";

namespace wendy
{
	CWindowsWindow::CWindowsWindow()
		: myHWND(nullptr)
		, myHInstance(nullptr)
	{
	}

	CWindowsWindow::~CWindowsWindow()
	{
		DestroyWindow(myHWND);
		myHWND = nullptr;

		UnregisterClass(szWindowClass, myHInstance);
		myHInstance = nullptr;
	}

	bool CWindowsWindow::Init(const SCreationParameters& aCreationParameters)
	{
		myHInstance = GetModuleHandle(nullptr);

		if (RegisterWindowsWindow(myHInstance) == false)
		{
			return false;
		}

		if (InitHWND(myHInstance, aCreationParameters.myWindowWidth, aCreationParameters.myWindowHeight) == false)
		{
			return false;
		}

		return true;
	}

	void CWindowsWindow::Update()
	{
		MSG windowsMessage = {};
		if (PeekMessage(&windowsMessage, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&windowsMessage);
			DispatchMessage(&windowsMessage);
		}
	}

	bool CWindowsWindow::LoadExtensionList(COpenGLFramework& aOpenGLFramework)
	{
		// Get the instance of this application.
		HINSTANCE hinstance = GetModuleHandle(NULL);

		// Give the application a name.
		const wchar_t* applicationName = L"temp";

		WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the window class.
		RegisterClassEx(&wc);

		// Create a temporary window for the OpenGL extension setup.
		HWND temphwnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName, WS_POPUP, 0, 0, 640, 480, NULL, NULL, hinstance, NULL);
		if (temphwnd == NULL)
		{
			return false;
		}

		// Don't show the window.
		ShowWindow(temphwnd, SW_HIDE);

		bool success = aOpenGLFramework.LoadExtensionList(temphwnd);

		DestroyWindow(temphwnd);

		return success;
	}

	bool CWindowsWindow::RegisterWindowsWindow(HINSTANCE aHInstance)
	{
		WNDCLASSEXW wcex = {};

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = &WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = (HINSTANCE)aHInstance;
		wcex.hIcon = LoadIcon((HINSTANCE)aHInstance, 0);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE);
		wcex.lpszMenuName = szTitle;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon((HINSTANCE)aHInstance, 0);

		ATOM result = RegisterClassEx(&wcex);
		if (result == 0)
		{
			assert(!"Failed to register Window Class");
			return false;
		}

		return true;
	}

	bool CWindowsWindow::InitHWND(void* aHInstance, const unsigned int aWindowWidth, const unsigned int aWindowHeight)
	{
		myHWND = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, aWindowWidth, aWindowHeight, nullptr, nullptr, (HINSTANCE)aHInstance, nullptr);

		if (myHWND == nullptr)
		{
			assert(!"Window failed to be created");
			return false;
		}

		(void)ShowWindow(myHWND, SW_SHOW);

		myIsOpen = true;

		BOOL updateWindowResult = UpdateWindow(myHWND);
		if (updateWindowResult == FALSE)
		{
			assert(!"Window failed to be updated");
			return false;
		}

		return true;
	}

	bool CWindowsWindow::InitInputWrapper(CInputManager& aInputManager)
	{
		return aInputManager.InitInputWrapper(myHWND, myHInstance);
	}

	void* CWindowsWindow::DeviceContext()
	{
		return GetDC(myHWND);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
	{
		RECT rect = {};
		GetWindowRect(hWnd, &rect);
		//PostMaster::GetInstance().SendLetter(Message(eMessageType::eWindowSizeChanged, EvWindowSizeChanged(rect.right - rect.left, rect.bottom - rect.top)));

		break;
	}
	case WM_ENTERSIZEMOVE:
		break;
	case WM_EXITSIZEMOVE:
		break;
	case WM_KILLFOCUS:
		//PostMaster::GetInstance().SendLetter(Message(eMessageType::eLostFocus, Event()));
		break;
	case WM_SETFOCUS:
		//PostMaster::GetInstance().SendLetter(Message(eMessageType::eGotFocus, Event()));
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		hdc;
		//TextOut(hdc, 300, 300, L"Hello Wendy!", 13);
		EndPaint(hWnd, &ps);
		break;
	}
	//case WM_QUIT:
	//	break;
	case WM_CLOSE:
	{
		wendy::CEngine* engine = wendy::CEngine::GetInstancePtr();
		if (engine)
		{
			engine->Shutdown();
		}
		break;
	}
	case WM_CREATE:
		break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
