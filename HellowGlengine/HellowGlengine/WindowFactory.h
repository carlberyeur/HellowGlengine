#pragma once

class IOSWindow;

class CWindowFactory
{
public:
	static IOSWindow* CreateWindow(const unsigned int aEngineCreationFlags);
};
