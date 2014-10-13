#pragma once

#ifndef CRAP_TIMER_MSVC_H
#define CRAP_TIMER_MSVC_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

namespace crap
{

typedef uint64_t tick_t;


CRAP_INLINE void timer_frequency( tick_t* tick )
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    *tick = freq.QuadPart;
}

CRAP_INLINE void timer_get_tick( tick_t* tick )
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    *tick = now.QuadPart;
}


CRAP_INLINE void yield_thread( void )
{
    YieldProcessor();
}

CRAP_INLINE void sleep_mil_sec(int millis)
{
    Sleep(millis);
}


} //namspace crap

#endif //CRAP_TIMER_MSVC_H
