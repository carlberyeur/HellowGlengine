#include "stdafx.h"
#include "OpenGLFramework.h"

#include <Windows.h>
#include <gl/GL.h>
#pragma comment(lib, "opengl32.lib")

struct DeviceContext 
{
	HDC member;
};

struct RenderingContext
{
	HGLRC member;
};

COpenGLFramework::COpenGLFramework()
	: myDeviceContext(nullptr)
	, myRenderingContext(nullptr)
{
}

COpenGLFramework::~COpenGLFramework()
{
}

bool COpenGLFramework::Init()
{
	return true;
}

void COpenGLFramework::ClearFrame()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void COpenGLFramework::Present()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void COpenGLFramework::UpdateWindowSize()
{
	throw std::logic_error("The method or operation is not implemented.");
}
