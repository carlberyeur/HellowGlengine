// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "CommonSTL.h"
#include "CommonCommonUtilities.h"
#include "CommonMacros.h"

#include "StopWatch.h"

#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr

// TODO: reference additional headers your program requires here
