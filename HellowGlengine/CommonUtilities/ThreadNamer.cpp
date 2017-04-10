#include "stdafx.h"
#include "ThreadNamer.h"

#include <windows.h>
#include <thread>

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

static std::map<uint32_t, std::string> locThreadNames;
static std::string locUnNamedThread("UnNamed");

namespace CU
{
	static const DWORD MS_VC_EXCEPTION = 0x406D1388;

	void SetThreadName(const std::string& threadName)
	{
		SetThreadName(GetCurrentThreadId(), threadName);
	}

	void SetThreadName(std::thread& thread, const std::string& threadName)
	{
		DWORD threadId = ::GetThreadId(static_cast<HANDLE>(thread.native_handle()));
		SetThreadName(threadId, threadName);
	}

	void SetThreadName(uint32_t dwThreadID, const std::string& threadName)
	{
		locThreadNames[dwThreadID] = threadName;

		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName.c_str();
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;

		__try
		{
			RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
		}
	}

	const std::string& GetThreadName()
	{
		DWORD id = GetCurrentThreadId();
		return GetThreadName(id);
	}

	const std::string& GetThreadName(std::thread& aThread)
	{
		DWORD id = ::GetThreadId(static_cast<HANDLE>(aThread.native_handle()));
		return GetThreadName(id);
	}

	const std::string& GetThreadName(const uint32_t aThreadID)
	{
		if (locThreadNames.find(aThreadID) != locThreadNames.end())
		{
			return locThreadNames[aThreadID];
		}

		return locUnNamedThread;
	}
}
