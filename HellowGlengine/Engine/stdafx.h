// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <cstdio>
#include <stdexcept>
#include <cassert>
#include <functional>
#include <map>
#include <string>
#include <fstream>

#include "../CommonUtilities/StopWatch.h"
#include "../CommonUtilities/GrowingArray.h"
#include "../CommonUtilities/StaticArray.h"

#include "../CommonUtilities/vector2.h"
#include "../CommonUtilities/vector3.h"
#include "../CommonUtilities/vector4.h"

#include "Engine.h"
#include "OpenGLFramework.h"
#include "WindowsWindow.h"

#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr
#define SAFE_DELETE_ARRAY(array_ptr) delete[] array_ptr; array_ptr = nullptr

// TODO: reference additional headers your program requires here
