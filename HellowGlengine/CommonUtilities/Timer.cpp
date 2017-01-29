#include "stdafx.h"
#include "Timer.h"

namespace CU
{
	CTimer::CTimer()
		: myLifeTime(0.f)
		, myDeltaTime(0.f)
	{
	}

	CTimer::~CTimer()
	{
	}

	void CTimer::Update()
	{
		std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaTime = time - myLastTimePoint;
		
		myDeltaTime = deltaTime.count();
		myLifeTime += myDeltaTime;

		myLastTimePoint = time;
	}
}