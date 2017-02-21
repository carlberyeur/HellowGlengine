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
	, myHasTakenInput(false)
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
	if (!myHasTakenInput)
	{
		return;
	}

	CInputMessage mouseMoved(CInputMessage::eType::eMouseMoved, static_cast<short>(myMouseDelta.x), static_cast<short>(myMouseDelta.y));
	for (IInputListener* listener : myInputListeners)
	{
		if (listener->TakeInput(mouseMoved) == IInputListener::eResult::eStop)
		{
			break;
		}
	}

	for (const CInputMessage& message : myBuffers[myRead])
	{
		for (IInputListener* listener : myInputListeners)
		{
			if (listener->TakeInput(message) == IInputListener::eResult::eStop) //TODO: console will break for key presses and then scene might not recieve mouse messages
			{
				break;
			}
		}
	}

	myBuffers[myRead].RemoveAll();
	myHasTakenInput = false;

	//myCopyMutex.lock();

	//unsigned char read = myRead;
	//myRead = myFree;
	//myFree = read;

	//myCopyMutex.unlock();
}

void CInputManager::Update()
{
	if (!myInputWrapper->Update())
	{
		return;
	}

	if (!myHasTakenInput && !myBuffers[myWrite].Empty())
	{
		//myCopyMutex.lock();

		unsigned char write = myWrite;
		myWrite = myRead;
		myRead = write;
		//unsigned char free = myFree;
		//myFree = myRead;
		//myRead = myWrite;
		//myWrite = free;

		//myCopyMutex.unlock();
	}

	//myCopyMutex.lock();

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
			CInputMessage keyReleasedMessage(CInputMessage::eType::eKeyboardPressed, keyReleased);
			myBuffers[myWrite].TryAdd(std::move(keyReleasedMessage));
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

	//myCopyMutex.unlock();
}

bool CInputManager::InitInputWrapper(void* aHWND, void* aHInstance)
{
	myInputWrapper = new CU::CDirectInputWrapper();
	return myInputWrapper && myInputWrapper->Init(static_cast<HINSTANCE>(aHInstance), static_cast<HWND>(aHWND));
}
