#include "stdafx.h"
#include "XInputWrapper.h"

#include "../CommonUtilities/vector2.h"

#include <Windows.h>
#include <Xinput.h>

#pragma comment (lib, "XInput.lib")

namespace CU
{
	typedef GrowingArray<XINPUT_STATE*>::size_type size_g;

	const unsigned short CXInputWrapper::GAMEPAD::DPAD_UP = XINPUT_GAMEPAD_DPAD_UP;
	const unsigned short CXInputWrapper::GAMEPAD::DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN;
	const unsigned short CXInputWrapper::GAMEPAD::DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT;
	const unsigned short CXInputWrapper::GAMEPAD::DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT;
	const unsigned short CXInputWrapper::GAMEPAD::START = XINPUT_GAMEPAD_START;
	const unsigned short CXInputWrapper::GAMEPAD::BACK = XINPUT_GAMEPAD_BACK;
	const unsigned short CXInputWrapper::GAMEPAD::LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB;
	const unsigned short CXInputWrapper::GAMEPAD::RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB;
	const unsigned short CXInputWrapper::GAMEPAD::LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER;
	const unsigned short CXInputWrapper::GAMEPAD::RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER;
	const unsigned short CXInputWrapper::GAMEPAD::A = XINPUT_GAMEPAD_A;
	const unsigned short CXInputWrapper::GAMEPAD::B = XINPUT_GAMEPAD_B;
	const unsigned short CXInputWrapper::GAMEPAD::X = XINPUT_GAMEPAD_X;
	const unsigned short CXInputWrapper::GAMEPAD::Y = XINPUT_GAMEPAD_Y;

#define THROW_AWAY_IF_LOW(LOW_VALUE, REAL_VALUE) ((std::abs(REAL_VALUE) - LOW_VALUE <= 0) ? REAL_VALUE : 0)

	CXInputWrapper::KeyStroke::eKeyState FlagsToKeyState(const WORD aFlag)
	{
		switch (aFlag)
		{
		case XINPUT_KEYSTROKE_KEYDOWN:
			return CXInputWrapper::KeyStroke::eKeyState::ePressed;
		case XINPUT_KEYSTROKE_KEYUP:
			return CXInputWrapper::KeyStroke::eKeyState::eReleased;
		case XINPUT_KEYSTROKE_REPEAT:
			return CXInputWrapper::KeyStroke::eKeyState::eRepeat;
		default:
			return CXInputWrapper::KeyStroke::eKeyState::eRepeat;
		}
	}

	CXInputWrapper::CXInputWrapper()
		: myJoysticks(2)
		, myDisconnectedJoysticks(2)
	{
	}

	CXInputWrapper::~CXInputWrapper()
	{
		myJoysticks.DeleteAll();

		if (myDisconnectedJoysticks.Size() > 0)
		{
			//post problem message?
			myDisconnectedJoysticks.DeleteAll();
		}
	}

	void CXInputWrapper::Init(const unsigned int aJoystickCount)
	{
		for (size_g i = 0; i < aJoystickCount; ++i)
		{
			myJoysticks.Add(new XINPUT_STATE());
		}
	}

	void CXInputWrapper::UpdateStates()
	{
		for (size_g i = 0; i < myJoysticks.Size(); ++i)
		{
			if (UpdateState(i) == false)
			{
				myDisconnectedJoysticks.Add(myJoysticks[i]);
			}
		}

		MoveDisconnectedJoysticks();
	}

	bool CXInputWrapper::GetKeyStroke(const unsigned int aJoystickIndex, KeyStroke& aKeyStrokeOutput)
	{
		XINPUT_KEYSTROKE keyStroke = {};

		unsigned int result = XInputGetKeystroke(aJoystickIndex, 0, &keyStroke);
		if (result == ERROR_SUCCESS)
		{
			aKeyStrokeOutput.myKeyState = FlagsToKeyState(keyStroke.Flags);
			aKeyStrokeOutput.myKeyCode = myJoysticks[aJoystickIndex]->Gamepad.wButtons;//keyStroke.VirtualKey;
			return true;
		}
		else if (result == ERROR_DEVICE_NOT_CONNECTED)
		{
			myDisconnectedJoysticks.Add(myJoysticks[aJoystickIndex]);
		}

		return false;
	}

	bool CXInputWrapper::GetKeyPressed(const unsigned int aJoystickIndex, const unsigned short aButton)
	{
		KeyStroke keyStroke = {};
		if (GetKeyStroke(aJoystickIndex, keyStroke) == true)
		{
			if (keyStroke.myKeyCode & aButton && keyStroke.myKeyState == KeyStroke::eKeyState::ePressed)
			{
				return true;
			}
		}

		return false;
	}

	bool CXInputWrapper::GetKeyReleased(const unsigned int aJoystickIndex, const unsigned short aButton)
	{
		KeyStroke keyStroke = {};
		if (GetKeyStroke(aJoystickIndex, keyStroke) == true)
		{
			if (keyStroke.myKeyCode & aButton && keyStroke.myKeyState == KeyStroke::eKeyState::eReleased)
			{
				return true;
			}
		}

		return false;
	}

	bool CXInputWrapper::IsConnected(const unsigned int aJoystickIndex, unsigned int* aError)
	{
		ZeroMemory(&myJoysticks[aJoystickIndex], sizeof(XINPUT_STATE));

		DWORD result = XInputGetState(aJoystickIndex, myJoysticks[aJoystickIndex]);

		if (aError != nullptr)
		{
			*aError = result;
		}

		if (result == ERROR_SUCCESS)
		{
			return true;
		}

		return false;
	}

	CU::Vector2f CXInputWrapper::GetRightStickPosition(const unsigned int aJoystickIndex)
	{
		CU::Vector2f position(myJoysticks[aJoystickIndex]->Gamepad.sThumbRX, myJoysticks[aJoystickIndex]->Gamepad.sThumbRY);

		if (position.Length2() < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			position = CU::Vector2f::Zero;
		}

		return position / SHRT_MAX;
	}

	CU::Vector2f CXInputWrapper::GetLeftStickPosition(const unsigned int aJoystickIndex)
	{
		CU::Vector2f position(myJoysticks[aJoystickIndex]->Gamepad.sThumbLX, myJoysticks[aJoystickIndex]->Gamepad.sThumbLY);

		if (position.Length2() < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			position = CU::Vector2f::Zero;
		}

		return position / SHRT_MAX;
	}

	bool CXInputWrapper::LeftStickIsInDeadzone(const unsigned int aJoystickIndex)
	{
		short x = myJoysticks[aJoystickIndex]->Gamepad.sThumbLX;
		short y = myJoysticks[aJoystickIndex]->Gamepad.sThumbLY;

		return THROW_AWAY_IF_LOW(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, x) == 0 && THROW_AWAY_IF_LOW(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, y) == 0;
	}

	bool CXInputWrapper::RightStickIsInDeadzone(const unsigned int aJoystickIndex)
	{
		short x = myJoysticks[aJoystickIndex]->Gamepad.sThumbRX;
		short y = myJoysticks[aJoystickIndex]->Gamepad.sThumbRY;

		return THROW_AWAY_IF_LOW(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, x) == 0 && THROW_AWAY_IF_LOW(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, y) == 0;
	}

	float CXInputWrapper::GetLeftTriggerDown(const unsigned int aJoystickIndex)
	{
		unsigned char trigger = myJoysticks[aJoystickIndex]->Gamepad.bLeftTrigger;

		return static_cast<float>(THROW_AWAY_IF_LOW(XINPUT_GAMEPAD_TRIGGER_THRESHOLD, trigger)) / static_cast<float>(UCHAR_MAX);
	}

	float CXInputWrapper::GetRightTringgerDown(const unsigned int aJoystickIndex)
	{
		unsigned char trigger = myJoysticks[aJoystickIndex]->Gamepad.bRightTrigger;

		return static_cast<float>(THROW_AWAY_IF_LOW(XINPUT_GAMEPAD_TRIGGER_THRESHOLD, trigger)) / static_cast<float>(UCHAR_MAX);
	}

	void CXInputWrapper::SetLeftVibration(const unsigned int aJoystickIndex, const unsigned short aAmount)
	{
		XINPUT_VIBRATION vibration = {};

		vibration.wLeftMotorSpeed = aAmount;
		//vibration.wRightMotorSpeed = 0.f;

		XInputSetState(aJoystickIndex, &vibration);
	}

	void CXInputWrapper::SetRightVibration(const unsigned int aJoystickIndex, const unsigned short aAmount)
	{
		XINPUT_VIBRATION vibration = {};

		//vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = aAmount;

		XInputSetState(aJoystickIndex, &vibration);
	}

	void CXInputWrapper::SetFullControllerVibration(const unsigned int aJoystickIndex, const unsigned short aAmount)
	{
		XINPUT_VIBRATION vibration = {};

		vibration.wLeftMotorSpeed = aAmount;
		vibration.wRightMotorSpeed = aAmount;

		XInputSetState(aJoystickIndex, &vibration);
	}

	void CXInputWrapper::StopVibration(const unsigned int aJoystickIndex)
	{
		XINPUT_VIBRATION vibration = {};

		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;

		XInputSetState(aJoystickIndex, &vibration);
	}

	unsigned int CXInputWrapper::GetConnectedJoystickCount() const
	{
		return myJoysticks.Size();
	}

	bool CXInputWrapper::UpdateState(const unsigned int aJoystickIndex)
	{
		ZeroMemory(myJoysticks[aJoystickIndex], sizeof(XINPUT_STATE));

		if (XInputGetState(aJoystickIndex, myJoysticks[aJoystickIndex]) == ERROR_SUCCESS)
		{
			return true;
		}

		return false;
	}

	void CXInputWrapper::MoveDisconnectedJoysticks()
	{
		for (size_g i = 0; i < myDisconnectedJoysticks.Size(); ++i)
		{
			myJoysticks.Remove(myDisconnectedJoysticks[i]);
		}

		myDisconnectedJoysticks.DeleteAll();
	}
}
