#include "stdafx.h"
#include "WorkPool.h"
#include "ThreadNamer.h"
#include "Work.h"

#include <queue>
#include <condition_variable>

namespace WorkPool
{
	using Worker = std::thread;

	static std::vector<Worker> locWorkers;
	static std::queue<Work> locWorks;

	static size_t locThreadCount = 0u;

	static std::mutex locQueueMutex;
	static std::condition_variable locConditionalVariable;
	static std::atomic_bool locIsStopped = true;

	void Process();
	bool CanEnter();

	bool Init(const bool aSingleThreaded)
	{
		locThreadCount = (aSingleThreaded) ? 1u : std::thread::hardware_concurrency();
		locWorkers.reserve(locThreadCount);

		locIsStopped = false;

		for (size_t i = 0; i < locThreadCount; ++i)
		{
			locWorkers.push_back(Worker(&Process));
			CU::SetThreadName(locWorkers.back(), "Worker " + std::to_string(i + 1));
		}

		return locWorkers.size() > 0;
	}

	void Shutdown()
	{
		std::unique_lock<std::mutex> backDoor(locQueueMutex);
		locIsStopped = true;
		locConditionalVariable.notify_all();
		backDoor.unlock();

		for (Worker& worker : locWorkers)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}

		locWorkers.clear();
	}

	void AddWork(Work&& aWork)
	{
		std::unique_lock<std::mutex> backDoor(locQueueMutex);
		locWorks.push(std::move(aWork));
		locConditionalVariable.notify_one();
	}

	void Process()
	{
		std::unique_lock<std::mutex> backDoor(locQueueMutex, std::defer_lock);

		while (true)
		{
			backDoor.lock();

			locConditionalVariable.wait(backDoor, CanEnter);

			if (locIsStopped) break;

			Work work = std::move(locWorks.front());
			locWorks.pop();

			backDoor.unlock();

			bool changeName = !work.GetName().empty();

			const std::string previousName = CU::GetThreadName();
			if (changeName) CU::SetThreadName(work.GetName());

			work.DoWork();

			if (changeName) CU::SetThreadName(previousName);

			if (!work.IsComplete() && !locIsStopped) AddWork(std::move(work));

			std::this_thread::yield();
		}
	}

	bool CanEnter()
	{
		return locIsStopped || !locWorks.empty();
	}
}
