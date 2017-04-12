#include "stdafx.h"
#include "ActivateRenderPackageCommand.h"
#include "RenderPackage.h"

namespace wendy
{
	CActivateRenderPackageCommand::CActivateRenderPackageCommand(IRenderPackage& aRenderPackage)
		: myRenderPackage(aRenderPackage)
	{
	}

	CActivateRenderPackageCommand::~CActivateRenderPackageCommand()
	{
	}

	void CActivateRenderPackageCommand::Do()
	{
		myRenderPackage.Activate();
	}
}
