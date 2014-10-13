#pragma once

#ifndef CRAP_THREAD_MSVC_H
#define CRAP_THREAD_MSVC_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

namespace crap
{

typedef void* thread_t;

CRAP_INLINE int32_t thread_create( thread_t* thread, void* (*start_routine) (void*), void* arg, uint32_t stacksize, uint32_t flags )
{
#if CRAP_PLATFORM_XBOX

    static volatile uint32_t coreCounter;
    uint32_t core = ((++coreCounter) * 2) % 12;

#endif

    *thread = CreateThread( 0x00, stacksize, (LPTHREAD_START_ROUTINE)start_routine, arg, flags, 0x00 );

#if CRAP_PLATFORM_XBOX

    XSetThreadProcessor(*thread, core >= 6 ? core - 5 : core);

#endif

    return ( *thread != 0x00 ) ? 0 : -1;
}

CRAP_INLINE int32_t thread_join( thread_t thread, void** retval )
{
    DWORD rc = WaitForSingleObject( thread, INFINITE);
    CloseHandle( thread );
    retval = 0x00;
    return (rc == WAIT_OBJECT_0) ? 0 : -1;
}

CRAP_INLINE int32_t thread_kill( thread_t thread )
{
    BOOL rc = TerminateThread( thread, 0 );
    CloseHandle( thread );
    return ( rc ) ? 0 : -1;
}

} //namspace crap

#endif //CRAP_THREAD_MSVC_H
