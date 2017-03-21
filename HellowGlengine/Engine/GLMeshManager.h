#pragma once
#include "MeshManager.h"

class CGLMeshManager : public IMeshManager
{
public:
	CGLMeshManager();
	~CGLMeshManager();

	CU::SharedPointer<IMesh> CreateQuad() override;
};
