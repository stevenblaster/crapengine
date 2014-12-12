#pragma once

#ifndef CRAP_MUTEX_MSVC_H
#define CRAP_MUTEX_MSVC_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

#ifdef CRAP_PLATFORM_WINDOWS || CRAP_PLATFORM_XBOX

namespace crap
{


typedef CRITICAL_SECTION mutex_t;

CRAP_INLINE int32_t mutex_init( mutex_t* mutex )
{
    InitializeCriticalSection(mutex);
    return 0;
}

CRAP_INLINE int32_t mutex_destroy( mutex_t* mutex )
{
    DeleteCriticalSection(mutex);
    return 0;
}

CRAP_INLINE int32_t mutex_lock( mutex_t* mutex)
{
    EnterCriticalSection(mutex);
    return 0;
}

CRAP_INLINE int32_t mutex_trylock( mutex_t* mutex )
{
    return TryEnterCriticalSection(mutex) ? 0 : 16;
}

CRAP_INLINE int32_t mutex_unlock( mutex_t* mutex )
{
    LeaveCriticalSection(mutex);
    return 0;
}


} //namspace crap

#endif //WIN/XBOX

#endif //CRAP_THREAD_MSVC_H
