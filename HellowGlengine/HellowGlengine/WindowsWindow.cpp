#include "stdafx.h"
#include "WindowsWindow.h"

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
const wchar_t szWindowClass[] = L"OpenGL testing";
const wchar_t szTitle[] = L"HellopenGL";

CWindowsWindow::CWindowsWindow()
{
}

CWindowsWindow::~CWindowsWindow()
{
}

bool CWindowsWindow::Init(const SCreationParameters& aCreationParameters)
{
	myHInstance = aCreationParameters.myWindowsParameters.myHInstance;

	if (RegisterWindowsWindow(aCreationParameters.myWindowsParameters.myHInstance) == false)
	{
		return false;
	}
	
	if (InitHWND(aCreationParameters.myWindowsParameters.myHInstance, aCreationParameters.myWindowWidth, aCreationParameters.myWindowHeight) == false)
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

		if (windowsMessage.message == WM_QUIT)
		{
			myIsOpen = false;
		}
	}
}

bool CWindowsWindow::RegisterWindowsWindow(void* aHInstance)
{
	WNDCLASSEXW wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
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

	ATOM result = RegisterClassExW(&wcex);
	if (result == 0)
	{
		assert(!"Failed to register Window Class");
		return false;
	}

	return true;
}

bool CWindowsWindow::InitHWND(void* aHInstance, const unsigned int aWindowWidth, const unsigned int aWindowHeight)
{
	myHWND = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, aWindowWidth, aWindowHeight, nullptr, nullptr, (HINSTANCE)aHInstance, nullptr);

	if (myHWND == nullptr)
	{
		assert(!"Window failed to be created");
		return false;
	}

	(void)ShowWindow((HWND)myHWND, SW_SHOW);
	
	myIsOpen = true;

	BOOL updateWindowResult = UpdateWindow((HWND)myHWND);
	if (updateWindowResult == FALSE)
	{
		assert(!"Window failed to be updated");
		return false;
	}

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOVE:
		break;
	case WM_MOVING:
		break;
	case WM_SIZE:
	{
		RECT rect = {};
		GetWindowRect(hWnd, &rect);
		//PostMaster::GetInstance().SendLetter(Message(eMessageType::eWindowSizeChanged, EvWindowSizeChanged(rect.right - rect.left, rect.bottom - rect.top)));

		break;
	}
	case WM_ENTERSIZEMOVE:
		break;
	case WM_KILLFOCUS:
		//PostMaster::GetInstance().SendLetter(Message(eMessageType::eLostFocus, Event()));
		break;
	case WM_SETFOCUS:
		//PostMaster::GetInstance().SendLetter(Message(eMessageType::eGotFocus, Event()));
		break;
	case WM_EXITSIZEMOVE:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 300, 300, L"Hello Wendy!", 13);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
		break;
	case WM_DESTROY:
		//Engine::GetInstance().SetIsRunning(false);
		PostQuitMessage(EXIT_SUCCESS);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
