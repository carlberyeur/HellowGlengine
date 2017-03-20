#pragma once

struct SSpriteVertex
{
	CU::Vector4f position;
	CU::Vector2f uv;
};

class IRenderObject
{
public:
	IRenderObject();
	virtual ~IRenderObject();

	virtual bool Init() = 0;
	virtual bool Init(const CU::StaticArray<SSpriteVertex, 4>& aVertices) = 0;
	virtual void Render() = 0;
};

