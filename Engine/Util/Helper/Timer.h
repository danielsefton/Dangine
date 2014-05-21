//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

#include "Platform/Prerequisites.h"
#include "Platform/Platform.h"

#if DANGINE_PLATFORM == DANGINE_PLATFORM_WIN32
# include "Util/Helper/Win32Timer.h"
#endif

#endif // TIMER_H