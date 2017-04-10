#pragma once

namespace CU
{
	class CWork;
}

using Work = CU::CWork;

namespace WorkPool
{
	bool Init(const bool aSingleThreaded = false);
	void Shutdown();
	void AddWork(Work&& aWork);
};
