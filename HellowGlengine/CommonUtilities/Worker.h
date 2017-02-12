#pragma once

namespace std
{
	class thread;
}

namespace CU
{
	class Work;
	class ThreadPool;

	class Worker
	{
	public:
		Worker();
		~Worker();

		void Init(ThreadPool& aThreadPool);
		void Stop();
		inline bool GetIsActive() { return isActive; }

	private:
		void Update();
		friend class ThreadPool;

		Work myWork;
		std::thread *myThread;
		ThreadPool *myPool;
		bool isActive;
		std::string myLogString;
	};
}
