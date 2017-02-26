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
	, myHasInputToDispatch(false)
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
	if (!myHasInputToDispatch)
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
	myHasInputToDispatch = false;
}

void CInputManager::Update()
{
	if (!myInputWrapper->Update())
	{
		return;
	}

	if (!myHasInputToDispatch && !myBuffers[myWrite].Empty())
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

	if (!myBuffers[myWrite].Empty())
	{
		myHasInputToDispatch = true;
	}

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
	myInputWrapper = CU::MakeUnique<CU::CDirectInputWrapper>();
	return myInputWrapper.IsValid() && myInputWrapper->Init(static_cast<HINSTANCE>(aHInstance), static_cast<HWND>(aHWND));
}
