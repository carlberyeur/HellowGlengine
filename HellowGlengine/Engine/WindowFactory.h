#pragma once

class IOSWindow;

class CWindowFactory
{
public:
	static CU::UniquePointer<IOSWindow> CreateWindow(const unsigned int aEngineCreationFlags);
};
