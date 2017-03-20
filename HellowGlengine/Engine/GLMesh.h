#pragma once
#include "Mesh.h"

class CGLMesh :	public IMesh
{
public:
	CGLMesh();
	CGLMesh(CGLMesh& aCopy);
	~CGLMesh();

	CGLMesh& operator=(CGLMesh& aCopy);

	bool Init() override;
	bool Init(const CU::StaticArray<SSpriteVertex, 4>& aVertices);
	void Render() override;

	void Destroy();

private:
	int myVertexCount;
	int myIndexCount;

	unsigned int myVertexArrayID;
	unsigned int myVertexBufferID;
	unsigned int myIndexBufferID;
};
