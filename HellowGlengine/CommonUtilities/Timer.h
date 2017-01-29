#pragma once

#include "Time.h"
#include <chrono>

namespace CU
{
	class CTimer
	{
	public:
		CTimer();
		~CTimer();

		void Update();

		inline Time GetLifeTime() const;
		inline Time GetDeltaTime() const;

	private:
		std::chrono::time_point<std::chrono::system_clock> myLastTimePoint;
		Time myLifeTime;
		Time myDeltaTime;
	};

	inline Time CTimer::GetLifeTime() const
	{
		return myLifeTime;
	}

	inline Time CTimer::GetDeltaTime() const
	{
		return myDeltaTime;
	}
}