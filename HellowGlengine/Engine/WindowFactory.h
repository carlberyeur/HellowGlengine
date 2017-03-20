#pragma once

class IWindow;

class CWindowFactory
{
public:
	static CU::UniquePointer<IWindow> Create(const unsigned int aEngineCreationFlags);
};
