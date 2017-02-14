// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "../CommonUtilities/CommonSTL.h"
#include "../CommonUtilities/CommonCommonUtilities.h"
#include "../CommonUtilities/CommonMacros.h"
#include "../CommonUtilities/StopWatch.h"

#include "Engine.h"
#include "OpenGLFramework.h"
#include "WindowsWindow.h"

#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr
#define SAFE_DELETE_ARRAY(array_ptr) delete[] array_ptr; array_ptr = nullptr
