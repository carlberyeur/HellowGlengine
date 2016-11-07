#include "stdafx.h"
#include "OpenGLFramework.h"

#include <Windows.h>
#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"

#pragma comment(lib, "opengl32.lib")

#define GetDeviceContext() reinterpret_cast<HDC>(myDeviceContext)
#define GetRenderingContext() reinterpret_cast<HGLRC>(myRenderingContext)

extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
//extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

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
	//float fieldOfView, screenAspect;
	//char *vendorString, *rendererString;
	LoadExtensionList();

	// Get the device context for this window.
	myDeviceContext = GetDC(GetFocus());
	if (myDeviceContext == nullptr)
	{
		return false;
	}

	int attributeListInt[19];
	// Support for OpenGL rendering.
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	// Support for rendering to a window.
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	// Support for hardware acceleration.
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	// Support for 24bit color.
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	// Support for 24 bit depth buffer.
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	// Support for double buffer.
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	// Support for swapping front and back buffer.
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	// Support for the RGBA pixel type.
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	// Support for a 8 bit stencil buffer.
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	// Null terminate the attribute list.
	attributeListInt[18] = 0;

	// Query for a pixel format that fits the attributes we want.
	int pixelFormat;
	unsigned int formatCount = 0;
	BOOL result = wglChoosePixelFormatARB(GetDeviceContext(), attributeListInt, nullptr, 1, &pixelFormat, &formatCount);
	if (result != TRUE) // == FALSE?
	{
		return false;
	}

	// If the video card/display can handle our desired pixel format then we set it as the current one.
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
	result = SetPixelFormat(GetDeviceContext(), pixelFormat, &pixelFormatDescriptor);
	if (result != TRUE)
	{
		return false;
	}


	// Set the 4.0 version of OpenGL in the attribute list.
	int attributeList[5];
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;

	// Null terminate the attribute list.
	attributeList[4] = 0;

	// Create a OpenGL 4.0 rendering context.
	myRenderingContext = wglCreateContextAttribsARB(GetDeviceContext(), 0, attributeList);
	if (myRenderingContext == nullptr)
	{
		return false;
	}

	// Set the rendering context to active.
	result = wglMakeCurrent(GetDeviceContext(), GetRenderingContext());
	if (result != TRUE)
	{
		return false;
	}

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