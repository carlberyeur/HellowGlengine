#include "stdafx.h"
#include "GLMeshManager.h"
#include "GLMesh.h"

CGLMeshManager::CGLMeshManager()
{
}

CGLMeshManager::~CGLMeshManager()
{
}

CU::UniquePointer<IMesh> CGLMeshManager::CreateQuad()
{
	CU::UniquePointer<IMesh> mesh = CU::MakeUnique<CGLMesh>();

	SSpriteVertex vertices[4];

	// Top left.
	vertices[0].position.x = 0.0f;
	vertices[0].position.y = 0.0f;
	vertices[0].position.z = 0.0f;

	vertices[0].uv.x = 0.0f;
	vertices[0].uv.y = 0.0f;

	// Bottom left.
	vertices[1].position.x = 0.0f;
	vertices[1].position.y = 1.0f;
	vertices[1].position.z = 0.0f;

	vertices[1].uv.x = 0.0f;
	vertices[1].uv.y = 1.0f;

	// Top right.
	vertices[2].position.x = 1.0f;
	vertices[2].position.y = 1.0f;
	vertices[2].position.z = 0.0f;

	vertices[2].uv.x = 1.0f;
	vertices[2].uv.y = 1.0f;

	// Bottom right.
	vertices[3].position.x = 1.0f;
	vertices[3].position.y = 0.0f;
	vertices[3].position.z = 0.0f;

	vertices[3].uv.x = 1.0f;
	vertices[3].uv.y = 0.0f;

	if (mesh->Init(vertices))
	{
		return mesh;
	}
	
	return CU::UniquePointer<IMesh>();
}
