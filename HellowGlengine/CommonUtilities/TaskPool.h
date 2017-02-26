#pragma once

class IWork;

namespace WorkPool
{
	bool Init();
	void Shutdown();
	void Process();
	bool AddWork(CU::UniquePointer<IWork> aWork);
};
