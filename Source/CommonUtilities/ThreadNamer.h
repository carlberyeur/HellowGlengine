#pragma once

namespace std
{
	class thread;
}

namespace CU
{
	void SetThreadName(const std::string& threadName);
	void SetThreadName(std::thread& thread, const std::string& threadName);
	void SetThreadName(uint32_t dwThreadID, const std::string& threadName);

	const std::string& GetThreadName();
	const std::string& GetThreadName(std::thread& aThread);
	const std::string& GetThreadName(const uint32_t aThreadID);
}