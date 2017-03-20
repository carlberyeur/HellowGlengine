#pragma once
#include "RenderObject.h"

class CGLRenderObject :	public IRenderObject
{
public:
	CGLRenderObject();
	CGLRenderObject(CGLRenderObject& aCopy);
	~CGLRenderObject();

	CGLRenderObject& operator=(CGLRenderObject& aCopy);

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
