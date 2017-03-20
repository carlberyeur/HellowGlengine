#pragma once
#include "MeshManager.h"

class CGLMeshManager : public IMeshManager
{
public:
	CGLMeshManager();
	~CGLMeshManager();

	CU::UniquePointer<IMesh> CreateQuad() override;
};
