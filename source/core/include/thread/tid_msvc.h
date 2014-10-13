#pragma once

#ifndef CRAP_TID_MSVC_H
#define CRAP_TID_MSVC_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

namespace crap
{

typedef uint32_t tid_t;
typedef uint32_t pid_t;

CRAP_INLINE tid_t thread_id( void )
{
#if CRAP_PLATFORM_XBOX

    return GetCurrentThreadId();

#elif CRAP_CPU_X64

    return ((uint32_t*) __readgsqword(48))[18];

#elif CRAP_CPU_X86

    return ((uint32_t*) __readfsdword(24))[9];

#endif

}


CRAP_INLINE pid_t process_id( void )
{
#if CRAP_PLATFORM_XBOX

    return 0;

#elif CRAP_CPU_X64

    return ((uint32_t*) __readgsqword(48))[16];

#elif CRAP_CPU_X86

    return ((uint32_t*) __readfsdword(24))[8];

#endif
}


} //namspace crap

#endif //CRAP_TID_MSVC_H
