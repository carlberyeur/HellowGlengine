#include "stdafx.h"
#include "InputManager.h"
#include "InputMessage.h"
#include "InputListener.h"

#include "../CommonUtilities/DInputWrapper.h"
#include "../CommonUtilities/EMouseButtons.h"

namespace wendy
{
	CInputManager* CInputManager::ourInstance = nullptr;

	CInputManager::CInputManager(IWindow& aWindow)
		: myInputListeners(8u)
		, myKeyList(8u)
		, myRead(0)
		, myWrite(1)
		, myHasInputToDispatch(false)
		, myIsRunning(false)
	{
		assert(!ourInstance);
		ourInstance = this;

		if (!aWindow.InitInputWrapper(*this))
		{
			DL_MESSAGE_BOX("Failed to initialize input wrapper");
		}
	}

	CInputManager::~CInputManager()
	{
		assert(ourInstance == this);
		ourInstance = nullptr;
	}

	void CInputManager::Start()
	{
		myIsRunning = true;

		mySleepTimer.Init();
		//while (myIsRunning)
		//{
		//	Update();
		//}
	}

	void CInputManager::Stop()
	{
		myIsRunning = false;
	}

	void CInputManager::DispatchMessages()
	{
		if (!myHasInputToDispatch)
		{
			return;
		}

		for (const CInputMessage& message : myBuffers[myRead])
		{
			for (IInputListener* listener : myInputListeners)
			{
				if (listener->TakeInput(message) == IInputListener::eResult::eStop)
				{
					break;
				}
			}
		}

		myBuffers[myRead].RemoveAll();
		myHasInputToDispatch = false;
	}

	void CInputManager::Update()
	{
		if (!myInputWrapper->Update())
		{
			return;
		}

		mySleepTimer.Update();
		if (mySleepTimer.GetLifeTime().Get<CU::MilliSeconds>() < 16.f)
		{
			std::this_thread::yield();
			return;
		}

		mySleepTimer.Restart();

		if (!myHasInputToDispatch && !myBuffers[myWrite].Empty())
		{
			if (myMouseDelta.Length2() > 0.001f)
			{
				CInputMessage mouseMovedMessage(CInputMessage::eType::eMouseMoved, static_cast<short>(myMouseDelta.x), static_cast<short>(myMouseDelta.y));
				myBuffers[myWrite].TryAdd(std::move(mouseMovedMessage));
			}

			unsigned char write = myWrite;
			myWrite = myRead;
			myRead = write;

			myHasInputToDispatch = true;
		}

		UpdateKeyboard();
		UpdateMouse();
	}

	bool CInputManager::IsRunning() const
	{
		return myIsRunning;
	}

	bool CInputManager::InitInputWrapper(void* aHWND, void* aHInstance)
	{
		myInputWrapper = CU::MakeUnique<CU::CDirectInputWrapper>();
		return myInputWrapper.IsValid() && myInputWrapper->Init(static_cast<HINSTANCE>(aHInstance), static_cast<HWND>(aHWND));
	}

	void CInputManager::UpdateKeyboard()
	{
		if (myInputWrapper->GetKeysPressed(myKeyList))
		{
			for (unsigned char keyPressed : myKeyList)
			{
				CInputMessage keyPressedMessage(CInputMessage::eType::eKeyboardPressed, keyPressed);
				myBuffers[myWrite].TryAdd(std::move(keyPressedMessage));
			}
		}

		if (myInputWrapper->GetKeysReleased(myKeyList))
		{
			for (unsigned char keyReleased : myKeyList)
			{
				CInputMessage keyReleasedMessage(CInputMessage::eType::eKeyboardReleased, keyReleased);
				myBuffers[myWrite].TryAdd(std::move(keyReleasedMessage));
			}
		}
	}

	void CInputManager::UpdateMouse()
	{
		for (int i = 0; i < static_cast<int>(CU::eMouseButton::eLength); ++i)
		{
			CU::eMouseButton button = static_cast<CU::eMouseButton>(i);

			if (myInputWrapper->IsMouseButtonPressed(button))
			{
				CInputMessage mousePressedMessage(CInputMessage::eType::eMousePressed, i);
				myBuffers[myWrite].TryAdd(std::move(mousePressedMessage));
			}

			if (myInputWrapper->IsMouseButtonReleased(button))
			{
				CInputMessage mouseReleasedMessage(CInputMessage::eType::eMouseReleased, i);
				myBuffers[myWrite].TryAdd(std::move(mouseReleasedMessage));
			}
		}

		myLastMousePosition = myMousePosition;
		if (myInputWrapper->GetMousePosition(myMousePosition))
		{
			myMouseDelta += myMousePosition - myLastMousePosition;
		}
	}
}
