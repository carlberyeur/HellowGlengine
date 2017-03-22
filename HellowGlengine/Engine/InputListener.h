#pragma once

namespace wendy
{
	class CInputMessage;

	class IInputListener
	{
	public:
		friend class CInputManager;
		enum class eResult
		{
			ePassOn,
			eStop
		};

		IInputListener();
		~IInputListener();

		void Subscribe();
		virtual eResult TakeInput(const CInputMessage& aMessage) = 0;

	private:
		int myPriority;
		bool mySubscribed;
	};
}
