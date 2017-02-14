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
	myReadBuffer = myWriteBuffer;
	myCopyMutex.unlock();

	for (CInputMessage message : myReadBuffer)
	{
		for (IInputListener* listener : myInputListeners)
		{
			if (listener->TakeInput(message) == IInputListener::eResult::eStop)
			{
				break;
			}
		}
	}
}

void CInputManager::Update()
{
	myCopyMutex.lock();

	if (myInputWrapper->GetKeysPressed(myKeyList))
	{
		for (unsigned char keyPressed : myKeyList)
		{
			CInputMessage keyPressedMessage(CInputMessage::eType::eKeyboardPressed, keyPressed);
			myWriteBuffer.TryAdd(std::move(keyPressedMessage));
		}
	}

	if (myInputWrapper->GetKeysReleased(myKeyList))
	{
		for (unsigned char keyReleased : myKeyList)
		{
			CInputMessage keyReleasedMessage(CInputMessage::eType::eKeyboardPressed, keyReleased);
			myWriteBuffer.TryAdd(std::move(keyReleasedMessage));
		}
	}

	myCopyMutex.unlock();
}

bool CInputManager::InitInputWrapper(void* aHWND, void* aHInstance)
{
	myInputWrapper = new CU::CDirectInputWrapper();
	return myInputWrapper && myInputWrapper->Init(static_cast<HINSTANCE>(aHInstance), static_cast<HWND>(aHWND));
}
