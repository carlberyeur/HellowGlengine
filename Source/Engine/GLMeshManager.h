#pragma once
#include "MeshManager.h"

namespace wendy
{
	class CGLMeshManager : public IMeshManager
	{
	public:
		CGLMeshManager();
		~CGLMeshManager();

		CU::SharedPointer<IMesh> CreateQuad() override;
	};
}
