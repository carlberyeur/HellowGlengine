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
		myRenderQueue.Add(aRenderCommand);
	}

	void CRenderer::Render()
	{
		DoRenderQueue();
	}

	void CRenderer::DoRenderQueue()
	{
		for (IRenderCommand* renderCommand : myRenderQueue)
		{
			renderCommand->Do();
		}

		myRenderQueue.DeleteAll();
	}
}
