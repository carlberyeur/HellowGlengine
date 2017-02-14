#include "stdafx.h"
#include "InputManager.h"
#include "InputMessage.h"
#include "InputListener.h"

#include "../CommonUtilities/DInputWrapper.h"

CInputManager* CInputManager::ourInstance(nullptr);

CInputManager::CInputManager(IOSWindow& aWindow)
	: myInputListeners(8u)
	, myKeyList(8u)
	, myIsStarted(false)
{
	assert(!ourInstance);
	ourInstance = this;

	aWindow.InitInputWrapper(*this);
}

CInputManager::~CInputManager()
{
	assert(ourInstance == this);
	ourInstance = nullptr;
}

void CInputManager::Start()
{
	myIsStarted = true;

	while (myIsStarted)
	{
		Update();
	}
}

void CInputManager::Stop()
{
	myIsStarted = false;
}

void CInputManager::DispatchMessages()
{
	if (!myHasFresh)
	{
		return;
	}

	myCopyMutex.lock();
	myHasFresh = false;
	myReadBuffer = myWriteBuffer;
	myCopyMutex.unlock();

	CInputMessage mouseMoved(CInputMessage::eType::eMouseMoved, static_cast<short>(myMouseDelta.x), static_cast<short>(myMouseDelta.y));
	for (IInputListener* listener : myInputListeners)
	{
		if (listener->TakeInput(mouseMoved) == IInputListener::eResult::eStop)
		{
			break;
		}
	}

	for (CInputMessage message : myReadBuffer)
	{
		for (IInputListener* listener : myInputListeners)
		{
			if (listener->TakeInput(message) == IInputListener::eResult::eStop) //TODO: console will break for key presses and then scene might not recieve mouse messages
			{
				break;
			}
		}
	}
}

void CInputManager::Update()
{
	if (!myInputWrapper->Update())
	{
		return;
	}

	myCopyMutex.lock();

	if (myInputWrapper->GetKeysPressed(myKeyList))
	{
		myHasFresh = true;
		for (unsigned char keyPressed : myKeyList)
		{
			CInputMessage keyPressedMessage(CInputMessage::eType::eKeyboardPressed, keyPressed);
			myWriteBuffer.TryAdd(std::move(keyPressedMessage));
		}
	}

	if (myInputWrapper->GetKeysReleased(myKeyList))
	{
		myHasFresh = true;
		for (unsigned char keyReleased : myKeyList)
		{
			CInputMessage keyReleasedMessage(CInputMessage::eType::eKeyboardPressed, keyReleased);
			myWriteBuffer.TryAdd(std::move(keyReleasedMessage));
		}
	}

	myLastMousePosition = myMousePosition;
	myInputWrapper->GetMousePosition(myMousePosition);
	myMouseDelta += myMousePosition - myLastMousePosition;

	//if (myMousePosition != myLastMousePosition)
	//{
	//	CU::Vector2i mouseDelta = myMousePosition - myLastMousePosition;

	//	CInputMessage mouseMovedMessage(CInputMessage::eType::eMouseMoved, mouseDelta.x, mouseDelta.y);
	//	myWriteBuffer.TryAdd(std::move(mouseMovedMessage));
	//}

	myCopyMutex.unlock();
}

bool CInputManager::InitInputWrapper(void* aHWND, void* aHInstance)
{
	myInputWrapper = new CU::CDirectInputWrapper();
	return myInputWrapper && myInputWrapper->Init(static_cast<HINSTANCE>(aHInstance), static_cast<HWND>(aHWND));
}
