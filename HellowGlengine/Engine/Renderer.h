#pragma once

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

	private:
		void DoRenderQueue();

	private:
		CU::GrowingArray<IRenderCommand*> myRenderQueue;
	};
}
