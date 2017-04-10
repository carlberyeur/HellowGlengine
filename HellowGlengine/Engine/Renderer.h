#pragma once
#include "../CommonUtilities/Synchronizer.h"

namespace wendy
{
	class IRenderCommand;

	class CRenderer
	{
	public:
		CRenderer();
		~CRenderer();

		void AddRenderCommand(IRenderCommand* aRenderCommand);
		void Render();

		void SwapRead();
		void SwapWrite();

	private:
		void DoRenderQueue();

		CSynchronizer<IRenderCommand*> mySynchronizer;
		CU::GrowingArray<IRenderCommand*> myRenderQueue;
	};
}
