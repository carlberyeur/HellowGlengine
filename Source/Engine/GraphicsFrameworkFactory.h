#pragma once

namespace wendy
{
	class IGraphicsFramework;
	class IWindow;

	class CGraphicsFrameworkFactory
	{
	public:
		static CU::UniquePointer<IGraphicsFramework> CreateFramework(const unsigned int aEngineFlags, IWindow& aWindow);
	};
}
