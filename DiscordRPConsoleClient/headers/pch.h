// Precompiled headers.
#pragma once

// Memory leak detection. (Windows only (debug))
#ifndef NDEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// Widely used headers.
#include <iostream>
#include <string>