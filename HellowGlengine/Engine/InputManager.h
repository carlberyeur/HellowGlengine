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
	CU::VectorOnStack<CInputMessage, 16, short, false> myWriteBuffer;
	CU::VectorOnStack<CInputMessage, 16, short, false> myReadBuffer;

	std::mutex myCopyMutex;

	CU::Vector2i myMousePosition;
	CU::Vector2i myLastMousePosition;
	CU::Vector2i myMouseDelta;

	CU::GrowingArray<IInputListener*> myInputListeners;
	CU::GrowingArray<unsigned char> myKeyList;

	CU::CDirectInputWrapper* myInputWrapper;

	bool myIsStarted;
	bool myHasFresh;

	static CInputManager* ourInstance;
};
