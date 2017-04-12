#pragma once
#include "RenderCommand.h"

namespace wendy
{
	class IRenderPackage;

	class CActivateRenderPackageCommand : public IRenderCommand
	{
	public:
		CActivateRenderPackageCommand(IRenderPackage& aRenderPackage);
		~CActivateRenderPackageCommand();

		virtual void Do() override;

	private:
		IRenderPackage& myRenderPackage;
	};
}
