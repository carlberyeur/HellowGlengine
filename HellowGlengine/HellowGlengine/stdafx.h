// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdexcept>
#include <assert.h>

#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr
#define SAFE_DELETE_ARRAY(array_ptr) delete[] array_ptr; array_ptr = nullptr

// TODO: reference additional headers your program requires here
