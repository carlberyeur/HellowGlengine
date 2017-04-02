#pragma once
#include "RenderCommand.h"


namespace wendy
{
	class IRenderPackage;

	class CDoPostEffectCommand : public IRenderCommand
	{
	public:
		CDoPostEffectCommand();
		~CDoPostEffectCommand();
	};
}
