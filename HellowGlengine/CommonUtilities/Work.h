#pragma once
#include <stdlib.h>
#include <functional>
#include <atomic>

namespace DL_Debug
{
	enum class eLogType;
}

namespace CU
{
	enum class ePriority
	{
		eHigh,
		eStandard,
		eLow
	};

	class Work
	{
	public:
		Work(std::function<void(void)> aFunction, ePriority aPrio = ePriority::eStandard);
		Work(std::function<void(void)> aFunction, DL_Debug::eLogType aToWhatLog, const char* aLogMessage, ePriority aPrio = ePriority::eStandard);
		Work(const Work& aWork);
		Work() {};
		~Work();

		void DoWork();
		inline ePriority GetPriority();

		std::string myLogMessage;
		DL_Debug::eLogType myToWhatLog;

	private:
		std::function<void(void)> myWork;
		ePriority myPrio;
	};

	ePriority Work::GetPriority()
	{
		return  myPrio;
	}

}