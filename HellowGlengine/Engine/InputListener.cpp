#include "stdafx.h"
#include "InputListener.h"
#include "InputManager.h"

IInputListener::IInputListener()
	: myPriority(0)
	, mySubscribed(false)
{
	if (CInputManager::ourInstance)
	{
		CInputManager::ourInstance->myInputListeners.Add(this);
		mySubscribed = true;
	}
}

IInputListener::~IInputListener()
{
	if (CInputManager::ourInstance)
	{
		CInputManager::ourInstance->myInputListeners.Remove(this);
	}
}

void IInputListener::Subscribe()
{
	if (!CInputManager::ourInstance)
	{
		assert(!"Input manager doesn't exist yet/anymore");
		return;
	}

	if (mySubscribed)
	{
		assert(!"Listener already subscribed!");
		return;
	}

	CInputManager::ourInstance->myInputListeners.Add(this);
	mySubscribed = true;
}
