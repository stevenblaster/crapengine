#pragma once

#ifndef CRAP_TIMER_GCC_H
#define CRAP_TIMER_GCC_H

#include "config/crap_platform.h"
#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_types.h"

#include <cstddef>
#include <ctime>
#if defined(CRAP_PLATFORM_MAC) || defined(CRAP_PLATFORM_IOS)
    #include <mach/mach_time.h>
#endif

namespace crap
{

typedef uint64_t tick_t;


CRAP_INLINE void timer_frequency( tick_t* tick )
{
#if CRAP_PLATFORM_MAC

    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    *tick = 1e9 * info.denom / info.numer;

#else

    *tick = 1e9;

#endif
}


CRAP_INLINE void timer_get_tick( tick_t* tick )
{
#if CRAP_PLATFORM_MAC

    *tick = mach_absolute_time();

#else

    struct timespec ticks;
    clock_gettime(CLOCK_MONOTONIC, &ticks);
    *tick = (uint64_t) ticks.tv_sec * 1000000000ull + ticks.tv_nsec;

#endif
}


CRAP_INLINE void yield_thread( void )
{
#if CRAP_CPU_X86 || CRAP_CPU_X64

    asm volatile("pause");

#endif
}


CRAP_INLINE void sleep_mil_sec( int32_t mil_sec )
{
    struct timespec ts;
    ts.tv_sec = mil_sec / 1000;
    ts.tv_nsec = (mil_sec % 1000) * 1000;
    nanosleep(&ts, 0x00);
}


} //namespace crap

#endif //CRAP_TID_GCC_H
