// Precompiled headers.
#pragma once

// Memory leak detection. (Visual Studio debugger)
#if defined(_DEBUG) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// Widely used headers.
#include <iostream>
#include <string>