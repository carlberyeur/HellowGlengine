#pragma once

#include "InputMessage.h"

namespace CU
{
	class CDirectInputWrapper;
}

namespace wendy
{
	class IWindow;
	class IInputListener;

	class CInputManager
	{
	public:
		friend class IInputListener;

		CInputManager(IWindow& aWindow);
		~CInputManager();

		void Start();
		void Stop();
		void DispatchMessages();

		void Update();
		bool IsRunning() const;

		bool InitInputWrapper(void* aHWND, void* aHInstance);

	private:
		void UpdateKeyboard();
		void UpdateMouse();

		CU::StaticArray<CU::VectorOnStack<CInputMessage, 16, short, false>, 2> myBuffers;

		CU::CStopWatch mySleepTimer;

		CU::GrowingArray<IInputListener*> myInputListeners;
		CU::GrowingArray<unsigned char> myKeyList;

		CU::Vector2i myMousePosition;
		CU::Vector2i myLastMousePosition;
		CU::Vector2i myMouseDelta;

		CU::UniquePointer<CU::CDirectInputWrapper> myInputWrapper;

		unsigned char myRead;
		unsigned char myWrite;

		std::atomic_bool myHasInputToDispatch;
		std::atomic_bool myIsRunning;

		static CInputManager* ourInstance;
	};
}
