// precompiled headers
#pragma once

// memory leak detection (debug only)
#ifndef NDEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#endif

// widely used headers
#include <iostream>
#include <string>