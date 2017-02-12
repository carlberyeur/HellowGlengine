#include "stdafx.h"

#include <Windows.h>
#include "glew\glew.h"
#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"

#pragma comment(lib, "opengl32.lib")
#ifdef _AMD64_
#pragma comment(lib, "../Dependencies/glew2.0.0/lib/Release/x64/glew32.lib")
#pragma comment(lib, "../Dependencies/glew2.0.0/lib/Release/x64/glew32s.lib")
#else
#pragma comment(lib, "../Dependencies/glew2.0.0/lib/Release/Win32/glew32.lib")
#pragma comment(lib, "../Dependencies/glew2.0.0/lib/Release/Win32/glew32s.lib")
#endif // _AMD64_


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

bool COpenGLFramework::Init(IOSWindow& aWindow)
{
	if (aWindow.LoadExtensionList(*this) == false)
	{
		return false;
	}


	// Get the device context for this window.
	myDeviceContext = GetDC(reinterpret_cast<HWND>(static_cast<CWindowsWindow&>(aWindow).GetHWND()));
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


	//char* vendorString = (char*)glGetString(GL_VENDOR);
	//char* rendererString = (char*)glGetString(GL_RENDERER);

	// Query for a pixel format that fits the attributes we want.
	int pixelFormat[1];
	unsigned int formatCount = 0;
	BOOL result = wglChoosePixelFormatARB(GetDeviceContext(), attributeListInt, nullptr, 1, pixelFormat, &formatCount);
	if (result != TRUE) // == FALSE?
	{
		DWORD errorCode = GetLastError();
		errorCode;
		return false;
	}

	// If the video card/display can handle our desired pixel format then we set it as the current one.
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
	int maxPixelFormatIndex = DescribePixelFormat(GetDeviceContext(), pixelFormat[0], sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);

	if (maxPixelFormatIndex == 0)
	{
		DWORD errorCode = GetLastError();
		errorCode;
		return false;
	}

	result = SetPixelFormat(GetDeviceContext(), pixelFormat[0], &pixelFormatDescriptor);
	if (result != TRUE)
	{
		DWORD errorCode = GetLastError();
		errorCode;
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
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void COpenGLFramework::Present()
{
	SwapBuffers(GetDeviceContext());
}

void COpenGLFramework::UpdateWindowSize()
{
	throw std::logic_error("The method or operation is not implemented.");
}
