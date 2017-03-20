#pragma once

class IMesh;

class IMeshManager
{
public:
	IMeshManager();
	virtual ~IMeshManager();

	virtual CU::UniquePointer<IMesh> CreateQuad() = 0;
};
