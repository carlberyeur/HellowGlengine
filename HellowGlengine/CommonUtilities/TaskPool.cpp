#include "stdafx.h"
#include "TaskPool.h"

#include <queue>
#include <memory>

class IWork
{

};

static CU::GrowingArray<CU::UniquePointer<IWork>> locWorks2;
static std::queue<std::unique_ptr<IWork>> locWorks;

namespace WorkPool
{
	bool Init()
	{
		return false;
	}

	void Shutdown()
	{
	}

	void Process()
	{
	}

	bool AddWork(std::unique_ptr<IWork> aWork)
	{
		locWorks.push(std::move(aWork));
		return true;
	}

	bool AddWork(CU::UniquePointer<IWork> aWork)
	{
		//locWorks.Add(std::move(aWork));
		return false;
	}
}
