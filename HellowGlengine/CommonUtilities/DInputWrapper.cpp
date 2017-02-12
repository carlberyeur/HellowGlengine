#include "stdafx.h"
#include "DInputWrapper.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define KEYBOARDKEYDOWN(key, name) ((name[static_cast<int>(key)] & 0x80) > 0)
#define KEYBOARDKEYUP(key, name) (!(name[static_cast<int>(key)] & 0x80))
#define MOUSEBUTTONDOWN(button, name) ((name.rgbButtons[static_cast<int>(button)] & 0x80) > 0)
#define MOUSEBUTTONUP(button, name) (!(name.rgbButtons[static_cast<int>(button)] & 0x80))

namespace CU
{
	InputWrapper::InputWrapper()
		: myKeyboardState(0)
		, myPreviousKeyboardState(0)
		, myMouseState({0})
		, myPreviousMouseState({0})
		, myDirectInputInterface(nullptr)
		, myKeyboard(nullptr)
		, myMouse(nullptr)
		, myIsInitialized(false)
	{
	}

	InputWrapper::~InputWrapper()
	{
	}

	bool InputWrapper::Init(HINSTANCE hinstance, HWND hwnd)
	{
		if (myIsInitialized == false)
		{
			HRESULT result = S_OK;

			result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&myDirectInputInterface, NULL);
			if (FAILED(result) == true)
			{
				return false;
			}

			result = myDirectInputInterface->CreateDevice(GUID_SysKeyboard, &myKeyboard, NULL);
			if (FAILED(result) == true)
			{
				return false;
			}

			result = myKeyboard->SetDataFormat(&c_dfDIKeyboard);
			if (FAILED(result) == true)
			{
				return false;
			}

			result = myKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if (FAILED(result) == true)
			{
				return false;
			}

			result = myDirectInputInterface->CreateDevice(GUID_SysMouse, &myMouse, NULL);
			if (FAILED(result) == true)
			{
				return false;
			}

			result = myMouse->SetDataFormat(&c_dfDIMouse);
			if (FAILED(result) == true)
			{
				return false;
			}

			result = myMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if (FAILED(result) == true)
			{
				return false;
			}

			myIsInitialized = true;

			bool finallyMadeIt = true;

			result = myKeyboard->Acquire();
			if (FAILED(result) == true)
			{
				finallyMadeIt = false;
			}

			result = myMouse->Acquire();
			if (FAILED(result) == true)
			{
				finallyMadeIt = false;
			}

			return finallyMadeIt;
		}
		return true;
	}

	void InputWrapper::Shutdown()
	{
		if (myMouse != nullptr)
		{
			myMouse->Unacquire();
			myMouse->Release();
			myMouse = nullptr;
		}

		if (myKeyboard != nullptr)
		{
			myKeyboard->Unacquire();
			myKeyboard->Release();
			myKeyboard = nullptr;
		}

		if (myDirectInputInterface != nullptr)
		{
			myDirectInputInterface->Release();
			myDirectInputInterface = nullptr;
		}
	}

	bool InputWrapper::Update()
	{
		if (myIsInitialized == true)
		{
			bool result = true;

			result = ReadKeyboard();
			if (result == false)
			{
				return false;
			}

			result = ReadMouse();
			if (result == false)
			{
				return false;
			}
		}
		return true;
	}

	void InputWrapper::GetMousePosition(int& aX, int& aY) const
	{
		POINT point;
		GetCursorPos(&point);
		aX = point.x;
		aY = point.y;
	}

	void InputWrapper::GetMousePosition(Vector2<int>& /*aMousePosition*/) const
	{
	}

	int InputWrapper::GetMousePositionX() const
	{
		POINT point;
		GetCursorPos(&point);
		return point.x;
	}

	int InputWrapper::GetMousePositionY() const 
	{
		POINT point;
		GetCursorPos(&point);
		return point.y;
	}

	int InputWrapper::GetMouseRelativePositionX() const
	{
		return myMouseState.lX;
	}

	int InputWrapper::GetMouseRelativePositionY() const
	{
		return myMouseState.lY;
	}

	void InputWrapper::SetMousePosition(const int aMouseX, const int aMouseY)
	{
		SetCursorPos(aMouseX, aMouseY);
	}

	bool InputWrapper::IsKeyboardKeyDown(eKeys aKey) const
	{
		return KEYBOARDKEYDOWN(aKey, myKeyboardState);
	}

	bool InputWrapper::IsKeyboardKeyPressed(eKeys aKey) const
	{
		return KEYBOARDKEYDOWN(aKey, myKeyboardState) && KEYBOARDKEYUP(aKey, myPreviousKeyboardState);
	}

	bool InputWrapper::IsKeyboardKeyReleased(eKeys aKey) const
	{
		return KEYBOARDKEYDOWN(aKey, myPreviousKeyboardState) && KEYBOARDKEYUP(aKey, myKeyboardState);
	}

	bool InputWrapper::IsMouseButtonDown(eMouseButtons aButton) const
	{
		return MOUSEBUTTONDOWN(aButton, myMouseState);
	}

	bool InputWrapper::IsMouseButtonPressed(eMouseButtons aButton) const
	{
		return MOUSEBUTTONDOWN(aButton, myMouseState) && MOUSEBUTTONUP(aButton, myPreviousMouseState);
	}

	bool InputWrapper::IsMouseButtonReleased(eMouseButtons aButton) const
	{
		return MOUSEBUTTONDOWN(aButton, myPreviousMouseState) && MOUSEBUTTONUP(aButton, myMouseState);
	}

	int InputWrapper::GetMouseWheelPos() const
	{
		return myMouseState.lZ / 120;
	}

	bool InputWrapper::GetKeysDown(GrowingArray<eKeys>& aKeysDown)
	{
		aKeysDown.RemoveAll();

		for (int i = 0; i < 256; ++i)
		{
			if (myKeyboardState[i] & 0x80)
			{
				aKeysDown.Add(static_cast<CU::eKeys>(i));
			}
		}

		return !aKeysDown.Empty();
	}

	bool InputWrapper::GetKeysPressed(GrowingArray<eKeys>& aKeysPressed)
	{
		aKeysPressed.RemoveAll();

		for (int i = 0; i < 256; ++i)
		{
			if ((myKeyboardState[i] & 0x80) && (myPreviousKeyboardState[i] ^ myKeyboardState[i]))
			{
				aKeysPressed.Add(static_cast<CU::eKeys>(i));
			}
		}

		return !aKeysPressed.Empty();
	}

	bool InputWrapper::GetKeysReleased(GrowingArray<eKeys>& aKeysReleased)
	{
		aKeysReleased.RemoveAll();

		for (int i = 0; i < 256; ++i)
		{
			if ((myPreviousKeyboardState[i] & 0x80) && (myPreviousKeyboardState[i] ^ myKeyboardState[i]))
			{
				aKeysReleased.Add(static_cast<CU::eKeys>(i));
			}
		}

		return !aKeysReleased.Empty();
	}

	bool InputWrapper::ReadKeyboard()
	{
		for (int i = 0; i < 256; ++i)
		{
			myPreviousKeyboardState[i] = myKeyboardState[i];
		}

		HRESULT result = myKeyboard->GetDeviceState(sizeof(myKeyboardState), (LPVOID)&myKeyboardState);

		if (FAILED(result) == true)
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				myKeyboard->Acquire();
			}
			else
			{
				return false;
			}
		}
		return true;	
	}
	bool InputWrapper::ReadMouse()
	{
		if (myIsInitialized == true)
		{
			myPreviousMouseState = myMouseState;

			HRESULT result = myMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&myMouseState);


			if (FAILED(result) == true)
			{
				if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
				{
					result = myMouse->Acquire();
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}
}
