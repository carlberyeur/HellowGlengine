#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "StaticArray.h"

namespace CU
{
	enum class eKeys;
	enum class eMouseButtons;
	
	template<typename T>
	class Vector2;

	class InputWrapper
	{
	public:
		InputWrapper();
		~InputWrapper();

		bool Init(HINSTANCE hinstance, HWND hwnd);
		void Shutdown();
		bool Update();

		void GetMousePosition(int& aX, int& aY) const;
		void GetMousePosition(Vector2<int>& aMousePosition) const;
		int GetMousePositionX() const;
		int GetMousePositionY() const;
		int GetMouseRelativePositionX() const;
		int GetMouseRelativePositionY() const;

		void SetMousePosition(const int aMouseX, const int aMouseY);

		bool IsKeyboardKeyDown(eKeys aKey) const;
		bool IsKeyboardKeyPressed(eKeys aKey) const;
		bool IsKeyboardKeyReleased(eKeys aKey) const;

		bool IsMouseButtonDown(eMouseButtons aButton) const;
		bool IsMouseButtonPressed(eMouseButtons aButton) const;
		bool IsMouseButtonReleased(eMouseButtons aButton) const;

		int GetMouseWheelPos() const;

		bool GetKeysDown(GrowingArray<eKeys>& aKeysDown);
		bool GetKeysPressed(GrowingArray<eKeys>& aKeysPressed);
		bool GetKeysReleased(GrowingArray<eKeys>& aKeysPressed);

	private:	
		bool ReadKeyboard();
		bool ReadMouse();

		CU::StaticArray<unsigned char, 256> myKeyboardState;
		CU::StaticArray<unsigned char, 256> myPreviousKeyboardState;

		DIMOUSESTATE myMouseState;
		DIMOUSESTATE myPreviousMouseState;

		IDirectInput8* myDirectInputInterface;
		IDirectInputDevice8* myKeyboard;
		IDirectInputDevice8* myMouse;

		bool myIsInitialized;
	};
}
