#include "stdafx.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include "GLRenderPackage.h"

namespace wendy
{
	CRenderer::CRenderer()
		: myRenderQueue(32u)
	{
		CGLRenderPackage package;
		package.Init({ 1024u, 1024u });
	}

	CRenderer::~CRenderer()
	{
		myRenderQueue.DeleteAll();
	}
	
	void CRenderer::AddRenderCommand(IRenderCommand* aRenderCommand)
	{
		if (!aRenderCommand) return;
		//myRenderQueue.Add(aRenderCommand);
		mySynchronizer.Write(aRenderCommand);
	}

	void CRenderer::Render()
	{
		DoRenderQueue();
	}

	void CRenderer::SwapRead()
	{
		mySynchronizer.SwapRead();
	}

	void CRenderer::SwapWrite()
	{
		mySynchronizer.SwapWrite();
	}

	void CRenderer::DoRenderQueue()
	{
		for (std::uint32_t i = 0; i < mySynchronizer.ReadSize(); i++)
		{
			IRenderCommand* renderCommand = mySynchronizer.At(i);
			if (renderCommand)
			{
				renderCommand->Do();
			}
		}
		//for (IRenderCommand* renderCommand : myRenderQueue)
		//{
		//	renderCommand->Do();
		//}

		//myRenderQueue.DeleteAll();
	}
}
