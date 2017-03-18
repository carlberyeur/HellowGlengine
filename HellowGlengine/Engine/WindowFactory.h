#pragma once

class IWindow;

class CWindowFactory
{
public:
	static CU::UniquePointer<IWindow> CreateWindow(const unsigned int aEngineCreationFlags);
};
