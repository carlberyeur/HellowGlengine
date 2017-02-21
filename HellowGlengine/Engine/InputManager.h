#pragma once

#include "InputMessage.h"

class IOSWindow;
class IInputListener;

namespace CU
{
	class CDirectInputWrapper;
}

class CInputManager
{
public:
	friend class IInputListener;

	CInputManager(IOSWindow& aWindow);
	~CInputManager();

	void Start();
	void Stop();
	void DispatchMessages();

	void Update();

	bool InitInputWrapper(void* aHWND, void* aHInstance);

private:
	CU::StaticArray<CU::VectorOnStack<CInputMessage, 16, short, false>, 3> myBuffers;

	std::mutex myCopyMutex;

	CU::Vector2i myMousePosition;
	CU::Vector2i myLastMousePosition;
	CU::Vector2i myMouseDelta;

	CU::GrowingArray<IInputListener*> myInputListeners;
	CU::GrowingArray<unsigned char> myKeyList;

	CU::UniquePointer<CU::CDirectInputWrapper> myInputWrapper;

	unsigned char myRead;
	unsigned char myWrite;
	unsigned char myFree;

	bool myHasInputToDispatch;
	bool myIsStarted;

	static CInputManager* ourInstance;
};
