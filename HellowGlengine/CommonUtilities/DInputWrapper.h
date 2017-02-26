#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "StaticArray.h"

namespace CU
{
	enum class eMouseButton;
	
	template<typename T>
	class Vector2;

	class CDirectInputWrapper
	{
	public:
		CDirectInputWrapper();
		~CDirectInputWrapper();

		bool Init(HINSTANCE hinstance, HWND hwnd);
		bool Update();

		void GetMousePosition(int& aX, int& aY) const;
		bool GetMousePosition(Vector2<int>& aMousePosition) const;
		int GetMousePositionX() const;
		int GetMousePositionY() const;
		int GetMouseRelativePositionX() const;
		int GetMouseRelativePositionY() const;

		void SetMousePosition(const int aMouseX, const int aMouseY);

		bool IsKeyboardKeyDown(unsigned char aKey) const;
		bool IsKeyboardKeyPressed(unsigned char aKey) const;
		bool IsKeyboardKeyReleased(unsigned char aKey) const;

		bool IsMouseButtonDown(eMouseButton aButton) const;
		bool IsMouseButtonPressed(eMouseButton aButton) const;
		bool IsMouseButtonReleased(eMouseButton aButton) const;

		int GetMouseWheelPos() const;

		bool GetKeysPressed(GrowingArray<unsigned char>& aKeysPressed);
		bool GetKeysReleased(GrowingArray<unsigned char>& aKeysPressed);

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
