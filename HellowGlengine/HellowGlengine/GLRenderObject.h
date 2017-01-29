#pragma once
#include "RenderObject.h"

class CGLEffect;

class CGLRenderObject :	public IRenderObject
{
public:
	CGLRenderObject();
	~CGLRenderObject();

	bool Init() override;
	void Render() override;

private:
	CGLEffect* myEffect;

	int myVertexCount;
	int myIndexCount;

	unsigned int myVertexArrayID;
	unsigned int myVertexBufferID;
	unsigned int myIndexBufferID;
};

