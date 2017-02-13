// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <Windows.h>

#ifdef _AMD64_

#ifdef _DEBUG

#undef _DEBUG
#include "../Dependencies/python34/include/Python.h"
#define _DEBUG

#else // !_DEBUG

#include "../Dependencies/python34/include/Python.h"

#endif // _DEBUG

#else // !_AMD64_

#error "No python libs for 32 bit :("

#endif // _AMD64_

#include "../CommonUtilities/CommonSTL.h"
#include "../CommonUtilities/CommonMacros.h"
#include "../CommonUtilities/CommonCommonUtilities.h"
#include "../CommonUtilities/CommandLineParser.h"

#include "PythonWrapper.h"
#include "PythonModule.h"
#include "PythonFunction.h"
#include "PythonTuple.h"
#include "PythonList.h"
