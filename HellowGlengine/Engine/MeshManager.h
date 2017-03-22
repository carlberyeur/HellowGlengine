#pragma once

namespace wendy
{
	class IMesh;

	class IMeshManager
	{
	public:
		IMeshManager();
		virtual ~IMeshManager();

		virtual CU::SharedPointer<IMesh> CreateQuad() = 0;
	};
}
