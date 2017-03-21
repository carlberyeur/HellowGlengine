#pragma once

namespace wendy
{
	class IRenderCommand
	{
	public:
		IRenderCommand() {}
		virtual ~IRenderCommand() {}

		virtual void Do() = 0;
	};
}
